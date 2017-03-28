
#ifndef ENYO_GAMEWINDOW_H
#define ENYO_GAMEWINDOW_H

#include "World.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

class Game
{
private:
	// Game Window
	sf::RenderWindow app;

	// Game World
	World mWorld;

private:
	void processEvents();
	void update();
	void render();
	void handlePlayerInput(sf::Keyboard::Key key, bool press);

public:
    Game(const uint32_t& width, const uint32_t& height);

	void run();
};

#endif //ENYO_GAMEWINDOW_H
