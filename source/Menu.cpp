
#include "Menu.h"

#include <iostream>
#include <SFML/Window/Event.hpp>

Menu::Menu(sf::RenderWindow& window, const uint32_t& width, const uint32_t& height)
        : textNumber(2), selectedItem(0), menuOptions{}, font(),  window(window),
          tBackground(), sBackground()
{
	if (!font.loadFromFile("fonts/cosmic_font.ttf"))
		throw std::runtime_error("Could not find font \"cosmic_font.ttf\"");

    menuOptions[0].setFont(font);
    menuOptions[0].setFillColor(sf::Color::Red);
    menuOptions[0].setString("Play");
    menuOptions[0].setPosition(sf::Vector2f(static_cast<float>(width / 2), static_cast<float>(height / (2 + 1) * 1)));

    menuOptions[1].setFont(font);
    menuOptions[1].setFillColor(sf::Color::White);
    menuOptions[1].setString("Exit");
    menuOptions[1].setPosition(sf::Vector2f(static_cast<float>(width / 2), static_cast<float>(height / (2 + 1) * 2)));

    tBackground.loadFromFile("images/menu_background.jpg");
    sBackground.setTexture(tBackground);
}

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

void Menu::draw()
{
    window.draw(sBackground);
    for (int i = 0; i < 2; i++)
        window.draw(menuOptions[i]);
}

int Menu::getSelectedOption()
{
    while(window.isOpen())
    {
        sf::Event event;

        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up)
                moveUp();
            else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down)
                moveDown();
            else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return)
                return selectedItem;
            else if(event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        draw();
        window.display();
    }

    return -1;
}
