#include "Game.h"
#include "Screen\TitleScreen.h"
#include "Screen\GameScreen.h"
#include <iostream>

namespace Pong
{
	Game::Game()
		: m_window { "Pong", sf::Vector2u{ 800,600 } }
		, m_elapsed { 0.0f }
		, m_screen { nullptr }
	{
		show_title_screen();
	}

	void Game::handle_input()
	{
		m_window.update();
	}

	void Game::update()
	{
		float timestep { 1.0f / 60.0f };

		if (m_elapsed >= timestep)
		{
			m_screen->update(m_elapsed);
			m_elapsed -= timestep;
		}
	}

	void Game::render()
	{
		m_window.begin_draw();

		sf::RenderWindow* w{ get_window()->get_render_window() };

		m_screen->draw(w);

		m_window.end_draw();
	}

	void Game::set_screen(Screen* screen)
	{
		if (m_screen != nullptr)
		{
			delete m_screen;
		}

		m_screen = screen;
		m_screen->on_start();
	}

	void Game::show_game_screen() { set_screen(new GameScreen()); }

	void Game::show_title_screen() { set_screen(new TitleScreen()); }

	void Game::show_credits_screen() { std::cout << "TODO: Show credits screen" << std::endl; }
}
