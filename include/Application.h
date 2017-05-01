#pragma once

#include "GameStage.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

class Application
{
private:
	sf::RenderWindow window;
	sf::Vector2i windowDimension;
	std::unique_ptr<GameStage> pStage;

	void run();

public:
	Application(const sf::Vector2i& windowDimension);
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	void runMenuStage();
	void runPlayStage();
};