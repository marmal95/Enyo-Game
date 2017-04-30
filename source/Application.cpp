#include "Application.h"
#include "Menu.h"
#include "GamePlay.h"

// Uncomment if want to DEBUG on Release
// #define _DEBUG

#ifdef _DEBUG
	#include <iostream>
#endif // DEBUG


#include <SFML/Window/Event.hpp>

Application::Application(const sf::Vector2i& windowDimension)
	: window(sf::VideoMode(static_cast<uint32_t>(windowDimension.x), static_cast<uint32_t>(windowDimension.y)),
		"The Enyo Game", sf::Style::Fullscreen),
	windowDimension(windowDimension), pStage(nullptr)
{
	window.setVerticalSyncEnabled(true);
}

void Application::run()
{
	#ifdef _DEBUG
		uint32_t fps = 0;
		float counter = 0.f;
	#endif

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
			
			#ifdef _DEBUG
				++fps;
				counter += dt;
				if (counter > 1.f)
				{
					std::cout << fps << std::endl;
					counter = 0.f;
					fps = 0;
				}
			#endif
	
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
