#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

namespace Pong
{
	class Window
	{
	public:
		Window();
		Window(const std::string& title, const sf::Vector2u size);
		~Window() {}

		void begin_draw();
		void end_draw();

		void update(sf::Event event);

		bool is_done() { return m_is_done; }
		bool is_fullscreen() { return m_is_fullscreen; }
		sf::RenderWindow* get_render_window() { return &m_window; }
		sf::Vector2u get_window_size() { return m_window_size; }

		void toggle_fullscreen();
	private:
		sf::RenderWindow m_window;
		sf::Vector2u m_window_size;
		std::string m_window_title;

		bool m_is_done;
		bool m_is_fullscreen;

		void create();
		void destroy();

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
	};
}
