#include "Screen/GameScreen.h"
#include "Random.h"
#include "Game.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

namespace Pong
{
	GameScreen::GameScreen(sf::Vector2u screen_size) : Screen{ screen_size }
	{
		init_gui();
	}

	void GameScreen::on_start()
	{
		m_ball.set_visibility(false);
		m_winner_text.set_visibility(false);
		m_press_key_text.set_visibility(false);

		m_p1_score = 0;
		m_p2_score = 0;
		m_p1_score_text.setString(std::to_string(m_p1_score));
		m_p2_score_text.setString(std::to_string(m_p1_score));

		m_p1_score_text.setPosition(m_screen_size.x * .25f - m_p1_score_text.getGlobalBounds().width / 2, k_score_vert_padding);
		m_p2_score_text.setPosition(m_screen_size.x * .75f - m_p2_score_text.getGlobalBounds().height / 2, k_score_vert_padding);

		float player_2_x_pos { -k_paddle_hori_padding + m_screen_size.x - m_p1.getSize().x };
		float player_vertical_center { m_screen_size.y / 2 - m_p1.getSize().y / 2 };

		m_p1.setPosition(k_paddle_hori_padding, player_vertical_center);
		m_p2.setPosition(player_2_x_pos, player_vertical_center);

		m_server = coin_toss() ? &m_p1 : &m_p2;

		m_state = PlayState::Serving;
	}
	
	void GameScreen::serve()
	{
		if (m_server == nullptr) return;

		const float ball_pos_x { m_screen_size.x / 2 - m_ball.getRadius() };
		const float ball_pos_y { 0 };

		m_ball.setPosition(ball_pos_x, ball_pos_x);
		m_ball.set_visibility(true);

		//m_ball.serve(m_server == &m_p1);
		//m_state = PlayState::Playing;
	}
	
	void GameScreen::tick(float delta_time)
	{
		// Move paddles
		if (PlayState::Playing == m_state || PlayState::Serving == m_state)
		{
			const bool did_press_w	  { sf::Keyboard::isKeyPressed(sf::Keyboard::W) };
			const bool did_press_s	  { sf::Keyboard::isKeyPressed(sf::Keyboard::S) };
			const bool did_press_up	  { sf::Keyboard::isKeyPressed(sf::Keyboard::Up) };
			const bool did_press_down { sf::Keyboard::isKeyPressed(sf::Keyboard::Down) };

			m_p1.move_up(did_press_w && can_go_up(m_p1));
			m_p1.move_down(did_press_s && can_go_down(m_p1));

			m_p2.move_up(did_press_up && can_go_up(m_p2));
			m_p2.move_down(did_press_down && can_go_down(m_p2));

			m_p1.tick(delta_time);
			m_p2.tick(delta_time);
		}

		if (PlayState::Won == m_state)
		{
			/* Wait for any key event to restart */
		}
		else if (PlayState::Serving == m_state)
		{
			m_time += delta_time;

			if (m_time >= k_serve_delay_sec)
			{
				serve();
				m_time = 0;
			}
		}
		else if (PlayState::Playing == m_state)
		{
			Paddle* m_winner = did_player_win();
			if (m_winner != nullptr)
			{
				m_ball.set_visibility(false);

				show_winner(m_winner->get_name());
				m_state = PlayState::Won;
				return;
			}

 			const bool did_p1_score{ m_ball.getPosition().x > m_screen_size.x };
			if (did_p1_score)
			{
				m_p1_score_text.setString(std::to_string(++m_p1_score));
				m_server = &m_p1;
			}

			const bool did_p2_score{ m_ball.getPosition().x + m_ball.getPosition().x < 0 };
			if (did_p2_score)
			{
				m_p2_score_text.setString(std::to_string(++m_p2_score));
				m_server = &m_p2;
			}

			if (did_p1_score || did_p2_score)
			{
				m_state = PlayState::Serving;
				return;
			}

			const bool did_hit_p1{ m_ball.getGlobalBounds().intersects(m_p1.getGlobalBounds()) };
			const bool did_hit_p2{ m_ball.getGlobalBounds().intersects(m_p2.getGlobalBounds()) };

			m_ball.tick(delta_time);
		}
	}

	void GameScreen::draw(sf::RenderTarget* target) const
	{
		target->draw(m_half_court_line);
		target->draw(m_p1);
		target->draw(m_p2);
		target->draw(m_ball);
		target->draw(m_p1_score_text);
		target->draw(m_p2_score_text);
		target->draw(m_winner_text);
		target->draw(m_press_key_text);
	}

	void GameScreen::handle_input(sf::Event event, Game* game)
	{
		if (PlayState::Won == m_state && event.type == sf::Event::KeyReleased) 
		{
			on_start();
		}
	}

	void GameScreen::init_gui()
	{
		m_p1.set_name("P1");
		m_p2.set_name("P2");

		m_winner_text.setCharacterSize(80);
		m_press_key_text.setCharacterSize(20);
	}

	Paddle* GameScreen::did_player_win()
	{
		bool did_p1_win { m_p1_score >= 5 };
		bool did_p2_win { m_p2_score >= 5 };

		return did_p1_win ? &m_p1 : did_p2_win ? &m_p2 : nullptr;
	}

	void GameScreen::show_winner(std::string name)
	{
		m_winner_text.setString("GG.\n" + name + " Wins!");
		m_winner_text.setPosition(m_screen_size.x / 2 - m_winner_text.getGlobalBounds().width / 2, 
			m_screen_size.y / 2 - m_winner_text.getGlobalBounds().height / 2);

		m_press_key_text.setPosition(m_winner_text.getGlobalBounds().width,
		                              m_winner_text.getGlobalBounds().height + m_winner_text.getGlobalBounds().height);

		m_winner_text.set_visibility(true);
		m_press_key_text.set_visibility(true);
	}

	bool GameScreen::can_go_up(const sf::RectangleShape& shape)
	{
		return shape.getPosition().y >= 0;
	}

	bool GameScreen::can_go_down(const sf::RectangleShape& shape)
	{
		return shape.getPosition().y + shape.getSize().y <= m_screen_size.y;
	}
}
