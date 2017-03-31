#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

class GameStage
{
public:
	GameStage();
	GameStage(const GameStage&) = delete;
	GameStage& operator=(const GameStage&) = delete;
	virtual ~GameStage();

public:
	virtual void init() = 0;
	virtual bool update(float dt) = 0;
	virtual void draw(sf::RenderWindow &window) = 0;
	virtual void release() = 0;
	virtual void handleUserInput(sf::Keyboard::Key key, bool pressed) = 0;
};
