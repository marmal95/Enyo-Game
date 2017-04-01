#include "Wall.h"

/**
 * Initializes Wall object
 * @param window window we draw on
 * @param animation wall animation - if exists
 * @param position wall position
 * @param angle wall rotation angle
 * @param sizeX wall size
 */
Wall::Wall(const GamePlay* window, const Animation &animation, const sf::Vector2f& position, const float &angle, const float &sizeX)
	: Entity(window, "Wall", animation, position, angle, sizeX)
{
}

/**
 * Updates Wall object.
 */
void Wall::update()
{
	Entity::update();
}