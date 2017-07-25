#include "Application.h"
#include "Constants.h"

#include <iostream>

int main()
{
	// Debudz
	srand((unsigned int) time(NULL));

	// Game Window Dimension
	const int game_width = WINDOW_WIDTH;
	const int game_height = WINDOW_HEIGHT;

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
