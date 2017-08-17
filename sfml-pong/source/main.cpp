#include "Game.h"
#include <iostream>

int main() 
{
	try
	{
		Pong::Game game;
		while (!game.get_window()->is_done()) {
			game.handle_input();
			game.update();
			game.render();
			game.restart_clock();
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Something went wrong." << std::endl;
	}

	return EXIT_SUCCESS;
}
