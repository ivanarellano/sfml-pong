#include <iostream>
#include "Window.h"
#include "TitleScreen.h"

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
