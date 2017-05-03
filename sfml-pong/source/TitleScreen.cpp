#include "TitleScreen.h"
#include <SFML/Window/Event.hpp>
#include "Window.h"
#include "GameScreen.h"

namespace Pong
{
	TitleScreen::TitleScreen()
	{
		m_title.set_size(80);
		m_host_game.set_size(20);
		m_join_game.set_size(20);
		m_credits.set_size(20);

		m_title.set_text("PONG");
		m_host_game.set_text("New Game (LAN)");
		m_join_game.set_text("Join Game (LAN)");
		m_credits.set_text("Credits");
	}

	void TitleScreen::new_game()
	{
	}

	void TitleScreen::join_game()
	{
	}

	void TitleScreen::on_start()
	{
		const int half_window = Window::k_width / 2;

		m_title.set_position(half_window - m_title.get_width() / 2, 100.f);
		m_host_game.set_position(half_window - m_host_game.get_width() / 2, 375.f);
		m_join_game.set_position(half_window - m_join_game.get_width() / 2, 425.f);
		m_credits.set_position(half_window - m_credits.get_width() / 2, 475.f);
	}

	void TitleScreen::draw(sf::RenderTarget* target)
	{
		m_title.draw(target);
		m_host_game.draw(target);
		m_join_game.draw(target);
		m_credits.draw(target);
	}

	void TitleScreen::update(float dt)
	{
	}

	void TitleScreen::handle_input(sf::Event event, Window* window)
	{
		if (event.type == sf::Event::MouseButtonReleased)
		{
			window->go_to_game_screen();
		}
	}

	void TitleScreen::on_stop()
	{
	}
}
