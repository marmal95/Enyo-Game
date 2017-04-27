#include "Application.h"
#include "Menu.h"
#include "GamePlay.h"

#include <iostream>

#include <SFML/Window/Event.hpp>

Application::Application(const sf::Vector2i& windowDimension)
	: window(sf::VideoMode(static_cast<uint32_t>(windowDimension.x), static_cast<uint32_t>(windowDimension.y)),
		"The Enyo Game", sf::Style::Default),
	windowDimension(windowDimension), pStage(nullptr)
{
	//window.setVerticalSyncEnabled(true);
}

void Application::run()
{
	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Window closed or escape key pressed: exit
			if ((event.type == sf::Event::Closed))
			{
				window.close();
				break;
			}

			if (event.type == sf::Event::KeyPressed)
				pStage->handleUserInput(event.key.code, true);
			if (event.type == sf::Event::KeyReleased)
				pStage->handleUserInput(event.key.code, false);
		}

		{
			float dt = clock.restart().asSeconds();
			std::cout << 1 / dt << std::endl;
			if (!pStage->update(dt))
				break;
		}

		window.clear();
		pStage->draw(window);
		window.display();
	}
}

void Application::runMenuStage()
{
	pStage.reset();
	pStage = std::make_unique<Menu>();

	pStage->init();
	this->run();

	Menu* menuPtr = dynamic_cast<Menu*>(pStage.get());
	switch (menuPtr->getSelectedOption())
	{
		case 0:
			runPlayStage();
			break;

		case 1:
			pStage.reset();
			window.close();
			break;

		default:break;
	}
}

void Application::runPlayStage()
{
	pStage.reset();
	pStage = std::make_unique<GamePlay>(window, windowDimension);

	pStage->init();
	this->run();
}
