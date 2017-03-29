#include "Game.h"

#include <SFML/Graphics.hpp>
#include "MapGenerator.h"


int main()
{
	srand(time(0));
    Game game(1920, 1200);
    game.run();

    return 0;
}
