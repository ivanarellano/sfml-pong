#include "Window.h"
#include <SFML/Window/Event.hpp>

namespace Pong
{
	Window::Window(const std::string& title, Screen* screen)
		: m_sf_render_thread { &Window::render_thread, this }
	{
		m_sf_window.create(sf::VideoMode(k_width, k_height), title);

		set_screen(screen);

		m_sf_window.setActive(false);

		m_sf_render_thread.launch();

		while (m_sf_window.isOpen())
		{
			poll_input_events();

			update_game_state();
		}

		shutdown();
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
				m_screen->handle_input(event);
			}
		}
	}

	void Window::update_game_state()
	{
		m_screen->update(m_frame_time.restart().asSeconds());
	}

	void Window::draw_frame()
	{
		while (m_sf_window.isOpen())
		{
			m_sf_window.clear();

			m_screen->draw(&m_sf_window);

			m_sf_window.display();
		}
	}

	void Window::shutdown() const
	{
		m_screen->on_stop();
	}

	void Window::render_thread()
	{
		draw_frame();
	}

	void Window::set_screen(Screen* screen)
	{
		m_screen = screen;
		m_screen->on_start();
	}
}