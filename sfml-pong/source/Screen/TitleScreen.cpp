#include "Screen/TitleScreen.h"
#include "Screen/GameScreen.h"
#include "Window.h"
#include <SFML/Window/Event.hpp>
#include <iostream>

namespace Pong
{
	TitleScreen::TitleScreen(sf::Vector2u screen_size) : Screen{ screen_size }
	{
		m_title.setCharacterSize(80);
		m_host_game.setCharacterSize(20);
		m_join_game.setCharacterSize(20);
		m_credits.setCharacterSize(20);
	}

	void TitleScreen::start_game_server()
	{
		std::cout << "TODO: Start server" << std::endl; /// TODO: Start server
	}

	void TitleScreen::find_game_server()
	{
		std::cout << "TODO: Start client" << std::endl; /// TODO: Start client
	}

	void TitleScreen::on_start()
	{
		const int half_w = m_screen_size.x / 2;

		m_title.setPosition(half_w - m_title.getGlobalBounds().width / 2, 100.f);
		m_host_game.setPosition(half_w - m_host_game.getGlobalBounds().width / 2, 375.f);
		m_join_game.setPosition(half_w - m_join_game.getGlobalBounds().width / 2, 425.f);
		m_credits.setPosition(half_w - m_credits.getGlobalBounds().width / 2, 475.f);
	}

	void TitleScreen::draw(sf::RenderTarget* target) const
	{
		target->draw(m_title);
		target->draw(m_host_game);
		target->draw(m_join_game);
		target->draw(m_credits);
	}

	void TitleScreen::handle_input(sf::Event event, Game* game)
	{
		if (event.type != sf::Event::MouseButtonReleased) {
			return;
		}

		auto pos = sf::Vector2f(sf::Mouse::getPosition(*game->get_window()->get_render_window()));

		if (m_host_game.getGlobalBounds().contains(pos.x, pos.y)) {
			m_host_game.on_click(this);
		}
		else if (m_join_game.getGlobalBounds().contains(pos.x, pos.y)) {
			m_join_game.on_click(this);
		}
		else if (m_credits.getGlobalBounds().contains(pos.x, pos.y)) {
			m_credits.on_click(game);
		}
	}
}
