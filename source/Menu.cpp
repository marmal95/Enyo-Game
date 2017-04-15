
#include "Menu.h"

#include <iostream>
#include <SFML/Window/Event.hpp>

/**
 * Initializes Menu
 */
Menu::Menu()
	: textNumber(2), selectedItem(0), menuOptions{}, font(),
	tBackground(), sBackground()
{}

/**
 * Selects higher menu option
 */
void Menu::moveUp()
{
	if (selectedItem - 1 >= 0)
	{
		menuOptions[selectedItem].setFillColor(sf::Color::White);
		selectedItem--;
		menuOptions[selectedItem].setFillColor(sf::Color::Red);
	}
}

/**
 * Selects lower menu option
 */
void Menu::moveDown()
{
	if (selectedItem + 1 < 2)
	{
		menuOptions[selectedItem].setFillColor(sf::Color::White);
		selectedItem++;
		menuOptions[selectedItem].setFillColor(sf::Color::Red);
	}
}

/**
 * Destructs menu
 */
Menu::~Menu()
{
	this->release();
}

/**
 * Get chosen option
 * @return selected option by user
 */
int Menu::getSelectedOption() const
{
	return selectedItem;
}

/**
 * Initializes menu. Loads resources.
 */
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

/**
 * Updates Menu until Space is clicked - menu option chosen
 * @param dt frame time
 * @return if keep updating
 */
bool Menu::update(float dt)
{
	return !sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
}

/**
 * Draws menu objects on screen
 * @param window window we draw on
 */
void Menu::draw(sf::RenderWindow& window)
{
	window.draw(sBackground);
	for (int i = 0; i < 2; i++)
		window.draw(menuOptions[i]);
}

/**
 * Deletes allocated objects
 */
void Menu::release()
{}

/**
 * Handles user input
 * @param key clicked key by user
 * @param pressed true - if pressed, false - if released
 */
void Menu::handleUserInput(sf::Keyboard::Key key, bool pressed)
{
	if (pressed && key == sf::Keyboard::Up)
		moveUp();
	if (pressed && key == sf::Keyboard::Down)
		moveDown();
}
