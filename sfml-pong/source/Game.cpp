#include "Game.h"
#include <iostream>

namespace Pong
{
	struct ServerUpdate
	{
		ServerUpdate(Server& server) : m_server{ &server } {}

		Server* m_server;

		void update()
		{
			if (m_server->start())
			{
				sf::Clock clock;
				clock.restart();

				while (m_server->is_running()) {
					m_server->update(clock.restart());
				}

				std::cout << "Stopping server..." << std::endl;
			}
		}

		void operator()() { update(); }
	};

	struct ClientUpdate
	{
		ClientUpdate(Client& client) : m_client{ &client } {}

		Client* m_client;

		void update()
		{
			sf::IpAddress ip{ "localhost" };
			PortNumber port{ 5600 };

			m_client->set_server_information(ip, port);
			m_client->setup(&handle_packet);

			if (m_client->connect())
			{
				sf::Clock clock;
				clock.restart();

				while (m_client->is_connected())
					m_client->update(clock.restart());
			}
			else
			{
				std::cout << "Failed to connect." << std::endl;
			}

			std::cout << "Quitting..." << std::endl;
		}

		void operator()() { update(); }
	};

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
