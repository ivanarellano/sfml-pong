#include "Window.h"
#include <SFML/Window/Event.hpp>

namespace Pong
{
	Window::Window(const std::string& title, Screen* screen)
	{
		m_sf_window.create(sf::VideoMode(k_width, k_height), title);
		m_sf_window.setFramerateLimit(60);

		set_screen(screen);

		while (m_sf_window.isOpen())
		{
			poll_input_events();
			update_game_state();
			draw_frame();
		}

		shutdown();
	}

	void Window::go_to_game_screen()
	{
		set_screen(new GameScreen());
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
		m_screen->update(m_frame_time.restart().asSeconds());
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
		m_screen = screen;
		m_screen->on_start();
	}
}
