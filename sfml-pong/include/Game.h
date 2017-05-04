#pragma once
#include "Window.h"
#include "Client.h"

namespace Pong
{
	class Game
	{
	public:
		Game();
		~Game();

		void update();
		void render();
		void late_update();

		sf::Time get_elapsed();

		Window* get_window();
	private:
		void restart_clock();

		sf::Clock m_clock;
		sf::Time m_elapsed;
		Window m_window;
		Client m_client;
	};
}
