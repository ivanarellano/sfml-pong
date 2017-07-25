#pragma once
#include "Client.h"
#include "Screen/Screen.h"
#include "Window.h"

namespace Pong
{
	class Game
	{
	public:
		Game();
		~Game() {}

		void handle_input();
		void update();
		void render();
		void restart_clock() { m_elapsed += m_clock.restart().asSeconds(); }

		sf::Time get_elapsed() { return m_clock.getElapsedTime(); }
		Window* get_window() { return &m_window; }
		
		void show_game_screen();
		void show_title_screen();
		void show_credits_screen();
	private:
		Window m_window;
		sf::Clock m_clock;
		float m_elapsed;
		Screen* m_screen;

		Client m_client;

		void set_screen(Screen* screen);
	};
}
