#include "Window.h"
#include <SFML/Window/Event.hpp>

namespace Pong
{
	Window::Window() : Window{ "Window", sf::Vector2u{ 800, 600 } }
	{
	}

	Window::Window(const std::string& title, const sf::Vector2u size)
		: m_window_title{ title }
		, m_window_size{ size }
		, m_is_fullscreen{ false }
		, m_is_done{ false }
	{
		create();
	}

	void Window::begin_draw()
	{
		m_window.clear(sf::Color::Black);
	}

	void Window::end_draw()
	{
		m_window.display();
	}

	void Window::update()
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) 
			{
				m_is_done = true;
			} 
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) 
			{
				m_is_done = true;
			} 
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5) 
			{
				toggle_fullscreen();
			}
		}
	}

	void Window::toggle_fullscreen()
	{
		m_is_fullscreen = !m_is_fullscreen;
		destroy();
		create();
	}

	void Window::create()
	{
		auto style = is_fullscreen() ? sf::Style::Fullscreen : sf::Style::Default;
		m_window.create(sf::VideoMode{ m_window_size.x, m_window_size.y, 32 }, m_window_title, style);
	}

	void Window::destroy()
	{
		m_window.close();
	}
}
