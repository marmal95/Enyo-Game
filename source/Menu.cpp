
#include "Menu.h"

#include <iostream>
#include <SFML/Window/Event.hpp>

Menu::Menu()
        : textNumber(2), selectedItem(0), menuOptions{}, font(),
          tBackground(), sBackground()
{}

void Menu::moveUp()
{
    if (selectedItem - 1 >= 0)
    {
        menuOptions[selectedItem].setFillColor(sf::Color::White);
        selectedItem--;
        menuOptions[selectedItem].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown()
{
    if (selectedItem + 1 < 2)
    {
        menuOptions[selectedItem].setFillColor(sf::Color::White);
        selectedItem++;
        menuOptions[selectedItem].setFillColor(sf::Color::Red);
    }
}

Menu::~Menu()
{
	this->release();
}

int Menu::getSelectedOption()
{
	return selectedItem;
}

void Menu::init()
{
	if (!font.loadFromFile("fonts/cosmic_font.ttf"))
		throw std::runtime_error("Could not find font \"cosmic_font.ttf\"");

	auto desktopMode = sf::VideoMode::getDesktopMode();

	menuOptions[0].setFont(font);
	menuOptions[0].setFillColor(sf::Color::Red);
	menuOptions[0].setString("Play");
	menuOptions[0].setPosition(sf::Vector2f(static_cast<float>(desktopMode.width / 2), static_cast<float>(desktopMode.height / (2 + 1) * 1)));

	menuOptions[1].setFont(font);
	menuOptions[1].setFillColor(sf::Color::White);
	menuOptions[1].setString("Exit");
	menuOptions[1].setPosition(sf::Vector2f(static_cast<float>(desktopMode.width / 2), static_cast<float>(desktopMode.height / (2 + 1) * 2)));

	tBackground.loadFromFile("images/menu_background.jpg");
	sBackground.setTexture(tBackground);
}

bool Menu::update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
		return false;
	return true;
}

void Menu::draw(sf::RenderWindow & window)
{
	window.draw(sBackground);
	for (int i = 0; i < 2; i++)
		window.draw(menuOptions[i]);
}

void Menu::release()
{}

void Menu::handleUserInput(sf::Keyboard::Key key, bool pressed)
{
	if (pressed && key == sf::Keyboard::Up)
		moveUp();
	if (pressed && key == sf::Keyboard::Down)
		moveDown();
}
