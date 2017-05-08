#include "Game.h"

namespace Pong
{
	Game::Game(): m_window { nullptr }
	{
	}

	Game::~Game()
	{
	}

	void Game::update()
	{
	}

	void Game::render()
	{
	}

	void Game::late_update()
	{
	}

	sf::Time Game::get_elapsed()
	{
		return m_clock.getElapsedTime();
	}

	Window* Game::get_window()
	{
		return &m_window;
	}

	void Game::restart_clock()
	{
	}
}
