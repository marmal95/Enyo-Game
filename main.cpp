#include <SFML/Graphics.hpp>

#include "Application.h"


int main()
{
	// For Debug
	srand(unsigned(time(NULL)));

	// Game Window Dimension
	const int game_width = 1920;
	const int game_height = 1200;

	Application app(sf::Vector2i(game_width, game_height));
	app.runMenuStage();

	return 0;
}
