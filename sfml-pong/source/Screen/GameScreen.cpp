#include "Screen/GameScreen.h"
#include "Random.h"
#include "Game.h"
#include <SFML/Window/Event.hpp>

namespace Pong
{
	GameScreen::GameScreen(sf::Vector2u screen_size) : Screen{ screen_size }
	{
		m_winner_text.setCharacterSize(80);
		m_press_key_text.setCharacterSize(20);
	}

	void GameScreen::on_start()
	{
		m_winner_text.set_visibility(false);
		m_press_key_text.set_visibility(false);

		m_ball.setOrigin(m_ball.getRadius(), m_ball.getRadius());
		m_ball.set_visibility(false);

		m_p1.setOrigin(m_p1.get_half_width(), m_p1.get_half_height());
		m_p2.setOrigin(m_p2.get_half_width(), m_p2.get_half_height());
		m_p1.setPosition(k_paddle_hori_padding, get_half_screen_height());
		m_p2.setPosition(m_screen_size.x - k_paddle_hori_padding, get_half_screen_height());

		m_p1_score = 0;
		m_p2_score = 0;
		m_p1_score_text.setString(std::to_string(m_p1_score));
		m_p2_score_text.setString(std::to_string(m_p2_score));

		m_p1_score_text.setOrigin(m_p1_score_text.get_half_width(), m_p1_score_text.get_half_height());
		m_p2_score_text.setOrigin(m_p2_score_text.get_half_width(), m_p2_score_text.get_half_height());
		m_p1_score_text.setPosition(m_screen_size.x * .25f, k_score_vert_padding);
		m_p2_score_text.setPosition(m_screen_size.x * .75f, k_score_vert_padding);

		m_server = coin_toss() ? &m_p1 : &m_p2;

		m_state = PlayState::Serving;
	}
	
	void GameScreen::serve()
	{
		if (m_server == nullptr) return;

		const double ball_y{ randomd(.15f, .85f) * m_screen_size.y };
		m_ball.setPosition(get_half_screen_width(), static_cast<float>(ball_y));
		m_ball.set_visibility(true);
		m_ball.serve(m_server == &m_p1);
		
		m_state = PlayState::Playing;
	}
	
	void GameScreen::tick(float delta_time)
	{
		m_p1.tick(delta_time);
		m_p2.tick(delta_time);

		if (PlayState::Serving == m_state)
		{
			m_serve_delay_dt += delta_time;
			if (m_serve_delay_dt >= k_serve_delay_sec)
			{
				serve();
				m_serve_delay_dt = 0;
			}
		}
		else if (PlayState::Playing == m_state)
		{
			Paddle* m_winner = did_player_win();
			if (m_winner != nullptr)
			{
				show_winner(m_winner->get_name());
				m_state = PlayState::Won;
				return;
			}

			check_scoring();

			m_ball.check_collision(m_p1, m_p2);

			m_ball.tick(delta_time);
		}
	}

	void GameScreen::check_scoring()
	{
		const bool did_p1_score{ m_ball.getPosition().x > m_screen_size.x + m_ball.getRadius() * 2 };
		const bool did_p2_score{ m_ball.getPosition().x < -m_ball.getRadius() * 2 };

		if (did_p1_score)
		{
			m_p1_score_text.setString(std::to_string(++m_p1_score));
			m_server = &m_p1;
		}

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
	}

	void GameScreen::draw(sf::RenderTarget* target) const
	{
		target->draw(m_half_court_line);

		if (m_ball.is_visible()) target->draw(m_ball);
		target->draw(m_p1);
		target->draw(m_p2);

		target->draw(m_p1_score_text);
		target->draw(m_p2_score_text);
		if (m_winner_text.is_visible()) target->draw(m_winner_text);
		if (m_press_key_text.is_visible()) target->draw(m_press_key_text);
	}

	void GameScreen::handle_input(sf::Event event, Game* game)
	{
		if (PlayState::Won == m_state && event.type == sf::Event::KeyReleased) 
		{
			on_start();
		}
	}

	Paddle* GameScreen::did_player_win()
	{
		bool did_p1_win { m_p1_score >= 5 };
		bool did_p2_win { m_p2_score >= 5 };

		return did_p1_win ? &m_p1 : did_p2_win ? &m_p2 : nullptr;
	}

	void GameScreen::show_winner(const std::string& name)
	{
		m_winner_text.setString("GG.\n" + name + " Wins!");

		m_winner_text.setPosition(
			m_screen_size.x / 2.f - m_winner_text.get_half_width(), 
			m_screen_size.y / 2.f - m_winner_text.get_half_height()
		);

		m_press_key_text.setPosition(
			m_winner_text.getPosition().x,
			m_winner_text.getPosition().y + m_winner_text.getGlobalBounds().height
		);

		m_winner_text.set_visibility(true);
		m_press_key_text.set_visibility(true);
	}
}
