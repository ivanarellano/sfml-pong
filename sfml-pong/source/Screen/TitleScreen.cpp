#include "Window.h"
#include "Screen/TitleScreen.h"
#include "Screen/GameScreen.h"
#include <SFML/Window/Event.hpp>
#include <iostream>

namespace Pong
{
	TitleScreen::TitleScreen()
		: m_title	  { "PONG", nullptr }
		, m_host_game { "New Game (LAN)", cb_new_game }
		, m_join_game { "Join Game (LAN)", cb_join_game }
		, m_credits	  { "Credits", cb_credits }
	{
		m_title.set_size(80);
		m_host_game.set_size(20);
		m_join_game.set_size(20);
		m_credits.set_size(20);
	}

	void TitleScreen::start_game_server()
	{
		// TODO: Start server
		std::cout << "TODO: Start server" << std::endl;
	}

	void TitleScreen::find_game_server()
	{
		// TODO: Start client
		std::cout << "TODO: Start client" << std::endl;
	}

	void TitleScreen::on_start()
	{
		const int half_window = Window::k_width / 2;

		m_title.set_position(half_window - m_title.get_bounds().width / 2, 100.f);
		m_host_game.set_position(half_window - m_host_game.get_bounds().width / 2, 375.f);
		m_join_game.set_position(half_window - m_join_game.get_bounds().width / 2, 425.f);
		m_credits.set_position(half_window - m_credits.get_bounds().width / 2, 475.f);
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
		if (event.type != sf::Event::MouseButtonReleased)
			return;

		auto pos = sf::Vector2f(sf::Mouse::getPosition(*window->get_render_window()));

		if (m_host_game.get_bounds().contains(pos.x, pos.y))
			m_host_game.on_click(this);
		else if (m_join_game.get_bounds().contains(pos.x, pos.y))
			m_join_game.on_click(this);
		else if (m_credits.get_bounds().contains(pos.x, pos.y))
			m_credits.on_click(window);
	}

	void TitleScreen::on_stop()
	{
	}
}
