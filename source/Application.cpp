#include "Application.h"
#include "Menu.h"
#include "GamePlay.h"

#include <SFML/Window/Event.hpp>

Application::Application(const sf::Vector2i& windowDimension)
	: window(sf::VideoMode(windowDimension.x, windowDimension.y), "The Enyo Game", sf::Style::Default),
	windowDimension(windowDimension), pStage(nullptr)
{
	window.setVerticalSyncEnabled(true);
}

void Application::run()
{
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

		if (!pStage->update(3))
			break;

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
	}
}

void Application::runPlayStage()
{
	pStage.reset();
	pStage = std::make_unique<GamePlay>(window, windowDimension);

	pStage->init();
	this->run();
}