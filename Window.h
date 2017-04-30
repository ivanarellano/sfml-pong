#pragma once
#include "Screen.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Thread.hpp>

namespace Pong
{
	class Window
	{
	public:
		constexpr static int k_width { 800 };
		constexpr static int k_height { 600 };

		Window(const std::string& title, Screen* screen);
	private:
		sf::RenderWindow m_sf_window;
		sf::Thread m_sf_render_thread;
		sf::Clock m_frame_time;
		Screen* m_screen;

		void poll_input_events();
		void update_game_state();
		void draw_frame();
		void shutdown() const;

		void set_screen(Screen* screen);
		void render_thread();

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
	};
}
