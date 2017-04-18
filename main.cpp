#include "Application.h"

#include <iostream>

int main()
{
	// Game Window Dimension
	const int game_width = 1920;
	const int game_height = 1200;

	try
	{
		Application app(sf::Vector2i(game_width, game_height));
		app.runMenuStage();
	}
	catch (const std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
		std::cin.get();
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}
