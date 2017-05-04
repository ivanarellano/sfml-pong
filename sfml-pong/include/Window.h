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

		Window(const std::string& title);

		sf::RenderWindow* get_render_window();

		void show_game_screen();
		void show_title_screen();
		void show_credits_screen();
	private:
		sf::RenderWindow m_sf_window;
		sf::Clock m_clock;
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
