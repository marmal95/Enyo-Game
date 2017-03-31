
#ifndef ENYO_MENU_H
#define ENYO_MENU_H

#include "GameStage.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <cstdint>

class Menu : public GameStage
{
private:
    size_t textNumber;
    int selectedItem;
    sf::Text menuOptions[2];

    sf::Font font;
    sf::Texture tBackground;
    sf::Sprite sBackground;

    void moveUp();
    void moveDown();

public:
    Menu();
	Menu(const Menu&) = delete;
	Menu& operator=(const Menu&) = delete;
	virtual ~Menu();

    int getSelectedOption();

	virtual void init() override;
	virtual bool update(float dt) override;
	virtual void draw(sf::RenderWindow &window) override;
	virtual void release() override;
	virtual void handleUserInput(sf::Keyboard::Key key, bool pressed) override;
};

#endif //ENYO_MENU_H
