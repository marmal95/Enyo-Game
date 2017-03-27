
#ifndef ENYO_MENU_H
#define ENYO_MENU_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <cstdint>

class Menu
{
private:
    size_t textNumber;
    int selectedItem;
    sf::Text menuOptions[2];

    sf::Font font;
    sf::Texture tBackground;
    sf::Sprite sBackground;

    sf::RenderWindow& window;

    void draw();
    void moveUp();
    void moveDown();

public:
    Menu(sf::RenderWindow& window, const uint32_t& width, const uint32_t& height);
    int getSelectedOption();
};

#endif //ENYO_MENU_H
