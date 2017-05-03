#include "TitleScreen.h"
#include <SFML/Window/Event.hpp>
#include "Window.h"
#include <iostream>

namespace Pong
{
	TitleScreen::TitleScreen()
	{
		m_title.set_text("PONG");
		m_host_game.set_text("PONG");
		m_join_game.set_text("PONG");
		m_credits.set_text("PONG");
	}

	void TitleScreen::on_start()
	{
		const int half_window = Window::k_width / 2;

		float title_w = m_title.get_width();
		float host_game_w = m_host_game.get_width();
		float join_game_w = m_join_game.get_width();
		float credits_w = m_credits.get_width();

		std::cout << host_game_w << std::endl;
		std::cout << join_game_w << std::endl;
		std::cout << credits_w << std::endl;

		m_title.set_position(half_window - title_w / 2, 100.f);
		m_host_game.set_position(half_window - host_game_w / 2, 200.f);
		m_join_game.set_position(half_window - join_game_w / 2, 300.f);
		m_credits.set_position(half_window - credits_w / 2, 500.f);
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

	void TitleScreen::handle_input(sf::Event event)
	{
	}

	void TitleScreen::on_stop()
	{
	}
}
