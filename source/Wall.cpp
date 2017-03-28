#include "Wall.h"

Wall::Wall(const World* window, const Animation &animation, const sf::Vector2f& position, const float &angle, const float &sizeX)
	: Entity(window, "Wall", animation, position, angle, sizeX)
{
}

void Wall::update()
{
	Entity::update();
}