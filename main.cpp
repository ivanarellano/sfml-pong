#include <iostream>

#include "Window.h"
#include "GameScreen.h"

int main() 
{
	try
	{
		Pong::GameScreen game_screen;
		Pong::Window window { "Pong",  &game_screen };
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
