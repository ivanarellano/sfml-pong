#include "Window.h"
#include "Screen/TitleScreen.h"
#include <iostream>

int main() 
{
	try
	{
		Pong::Window window { "Pong" };
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
