#include "GameScreen.h"
#include "Window.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

namespace Pong
{
	GameScreen::GameScreen() : GameScreen { 35.f, 40.f, 3 }
	{
		m_player_1.set_name("P1");
		m_player_2.set_name("P2");

		m_winner_text.set_size(80);
		m_press_key_text.set_size(20);
	}

	void GameScreen::on_start()
	{
		m_ball.set_visibility(View::Visibility::Gone);
		m_winner_text.set_visibility(View::Visibility::Gone);
		m_press_key_text.set_visibility(View::Visibility::Gone);

		m_p1_score = 0;
		m_p2_score = 0;
		m_p1_score_view.set_text(std::to_string(m_p1_score));
		m_p2_score_view.set_text(std::to_string(m_p1_score));

		m_p1_score_view.set_position(Window::k_width * .25f - m_p1_score_view.get_width() / 2, k_score_offset);
		m_p2_score_view.set_position(Window::k_width * .75f - m_p2_score_view.get_width() / 2, k_score_offset);

		const float player_2_x_pos{-k_paddle_offset + Window::k_width - m_player_1.get_width()};
		const float player_vertical_center{ Window::k_height / 2 - m_player_1.get_height() / 2};

		m_player_1.set_position(k_paddle_offset, player_vertical_center);
		m_player_2.set_position(player_2_x_pos, player_vertical_center);

		m_server = coin_toss() ? &m_player_1 : &m_player_2;

		m_state = PlayState::Serving;
	}
	
	void GameScreen::serve()
	{
		if (m_server == nullptr)
			return;

		Ball::Direction dir;

		if (m_server == &m_player_1)
		{
			dir = coin_toss() ? Ball::Direction::NE : Ball::Direction::SE;
		}
		else
		{
			dir = coin_toss() ? Ball::Direction::NW : Ball::Direction::SW;
		}

		const float ball_pos_x{ Window::k_width / 2 - m_ball.get_width() / 2};
		const float ball_pos_y{static_cast<float>(random(static_cast<int>(m_ball.get_height()), Window::k_height)) - m_ball.get_height() / 2};

		m_ball.set_direction(dir);
		m_ball.reset_velocity();
		m_ball.set_position(ball_pos_x, ball_pos_y);
		m_ball.set_visibility(View::Visibility::Visible);

		m_state = PlayState::Playing;
	}
	
	void GameScreen::update(float dt)
	{
		if (PlayState::Playing == m_state || PlayState::Serving == m_state)
		{
			const bool did_press_up{sf::Keyboard::isKeyPressed(sf::Keyboard::Up)};
			const bool did_press_down{sf::Keyboard::isKeyPressed(sf::Keyboard::Down)};
			const bool did_press_w{sf::Keyboard::isKeyPressed(sf::Keyboard::W)};
			const bool did_press_s{sf::Keyboard::isKeyPressed(sf::Keyboard::S)};

			m_player_1.move_up(did_press_w && can_go_up(m_player_1.get_shape()));
			m_player_1.move_down(did_press_s && can_go_down(m_player_1.get_shape()));

			m_player_2.move_up(did_press_up && can_go_up(m_player_2.get_shape()));
			m_player_2.move_down(did_press_down && can_go_down(m_player_2.get_shape()));

			m_player_1.update(dt);
			m_player_2.update(dt);
		}

		if (PlayState::Won == m_state)
		{
			/* Wait for any key event to restart */
		}
		else if (PlayState::Serving == m_state)
		{
			m_time += m_clock.getElapsedTime().asSeconds();
			m_clock.restart();

			if (m_time >= k_serve_delay)
			{
				serve();
				m_time = 0;
				m_clock.restart();
			}
		}
		else if (PlayState::Playing == m_state)
		{
			Paddle* m_winner = did_player_win();

			if (m_winner != nullptr)
			{
				m_ball.set_visibility(View::Visibility::Gone);

				show_winner(m_winner->get_name());
				m_state = PlayState::Won;
				return;
			}

			const bool did_p1_score{m_ball.get_shape().getPosition().x > Window::k_width};
			const bool did_p2_score{m_ball.get_shape().getPosition().x + m_ball.get_width() < 0};

			if (did_p1_score)
			{
				m_p1_score_view.set_text(std::to_string(++m_p1_score));
				m_server = &m_player_1;
			}

			if (did_p2_score)
			{
				m_p2_score_view.set_text(std::to_string(++m_p2_score));
				m_server = &m_player_2;
			}

			if (did_p1_score || did_p2_score)
			{
				m_state = PlayState::Serving;
				return;
			}

			const bool did_hit_p1{m_ball.get_shape().getGlobalBounds().intersects(m_player_1.get_shape().getGlobalBounds())};
			const bool did_hit_p2{m_ball.get_shape().getGlobalBounds().intersects(m_player_2.get_shape().getGlobalBounds())};

			if (did_hit_p1 || did_hit_p2)
				m_ball.reflect_on_paddle();

			if (!can_go_up(m_ball.get_shape()) || !can_go_down(m_ball.get_shape()))
				m_ball.reflect_on_court();

			m_ball.update(dt);
		}
	}

	void GameScreen::draw(sf::RenderTarget* target)
	{
		m_half_court_line.draw(target);
		m_player_1.draw(target);
		m_player_2.draw(target);
		m_ball.draw(target);
		m_p1_score_view.draw(target);
		m_p2_score_view.draw(target);
		m_winner_text.draw(target);
		m_press_key_text.draw(target);
	}

	void GameScreen::handle_input(sf::Event event)
	{
		if (PlayState::Won == m_state)
			on_start();
	}

	Paddle* GameScreen::did_player_win()
	{
		bool did_p1_win{m_p1_score >= 5};
		bool did_p2_win{m_p2_score >= 5};

		return did_p1_win ? &m_player_1 : did_p2_win ? &m_player_2 : nullptr;
	}

	void GameScreen::show_winner(std::string name)
	{
		m_winner_text.set_text("GG.\n" + name + " Wins!");
		m_winner_text.set_position(Window::k_width / 2 - m_winner_text.get_width() / 2, 
			Window::k_height / 2 - m_winner_text.get_height() / 2);

		m_press_key_text.set_text("Press any key\nto play again.");
		m_press_key_text.set_position(m_winner_text.get_position().x,
		                              m_winner_text.get_position().y + m_winner_text.get_height());

		m_winner_text.set_visibility(View::Visibility::Visible);
		m_press_key_text.set_visibility(View::Visibility::Visible);
	}

	bool GameScreen::can_go_up(const sf::RectangleShape& shape)
	{
		return shape.getPosition().y >= 0;
	}

	bool GameScreen::can_go_down(const sf::RectangleShape& shape)
	{
		return shape.getPosition().y + shape.getSize().y <= Window::k_height;
	}
}
