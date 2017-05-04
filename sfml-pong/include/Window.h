#pragma once
#include "Screen.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameScreen.h"

namespace Pong
{
	class Window
	{
	public:
		virtual ~Window() {}

		constexpr static int k_width { 800 };
		constexpr static int k_height { 600 };

		Window(const std::string& title, Screen* screen);

		virtual void go_to_game_screen();
	private:
		sf::RenderWindow m_sf_window;
		sf::Clock m_frame_time;
		Screen* m_screen;

		void poll_input_events();
		void update_game_state();
		void draw_frame();
		void shutdown() const;

		void set_screen(Screen* screen);

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
	};
}
