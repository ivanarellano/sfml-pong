#include "Window.h"
#include "GameScreen.h"
#include "TitleScreen.h"
#include <SFML/Window/Event.hpp>
#include <thread>
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

	Window::Window(const std::string& title) : m_screen { nullptr }, m_server { server_handler }
	{
		m_sf_window.create(sf::VideoMode(k_width, k_height), title);
		m_sf_window.setFramerateLimit(60);

		show_title_screen();

		std::thread server_thread { ServerUpdate(m_server) };

		while (m_sf_window.isOpen())
		{
			poll_input_events();
			update_game_state();
			draw_frame();
		}

		shutdown();

		server_thread.join();
	}

	sf::RenderWindow* Window::get_render_window()
	{
		return &m_sf_window;
	}

	void Window::show_game_screen()
	{
		set_screen(new GameScreen());
	}

	void Window::show_title_screen()
	{
		set_screen(new TitleScreen());
	}

	void Window::show_credits_screen()
	{
		// TODO: Show credits
		std::cout << "TODO: Show credits" << std::endl;
	}

	void Window::poll_input_events()
	{
		sf::Event event;

		while (m_sf_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_sf_window.close();
			}
			else 
			{
				if (m_screen != nullptr)
					m_screen->handle_input(event, this);
			}
		}
	}

	void Window::update_game_state()
	{
		m_screen->update(m_clock.restart().asSeconds());
	}

	void Window::draw_frame()
	{
		m_sf_window.clear();

		m_screen->draw(&m_sf_window);

		m_sf_window.display();
	}

	void Window::shutdown() const
	{
		m_screen->on_stop();
	}

	void Window::set_screen(Screen* screen)
	{
		if (m_screen != nullptr)
		{
			m_screen->on_stop();
			delete m_screen;
		}

		m_screen = screen;
		m_screen->on_start();
	}
}
