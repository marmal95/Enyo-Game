#include <SFML/Window/Event.hpp>

#include "Game.h"
#include "Entity.h"

Game::Game(const uint32_t & width, const uint32_t & height)
	: app(sf::VideoMode(width, height), "The Enyo Game"), mWorld(app, sf::Vector2i(width, height))
{
	app.setFramerateLimit(60);
}

void Game::run()
{
	while (app.isOpen())
	{
		processEvents();
		update();
		render();
	}
}


void Game::processEvents()
{
	mWorld.processEvents();
}

void Game::update()
{
	mWorld.update();
}

void Game::render()
{
	// Clear Window
	app.clear();

	// Draw Whole World
	mWorld.draw();

	// Display in Game Window
	app.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool press)
{

}
