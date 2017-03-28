
#include "Explosion.h"

/**
 * Initializes Explosion Object
 * @param animation object animation
 * @param x x - axis position
 * @param y y - axis position
 * @param angle direction angle
 * @param radius object radius
 */
Explosion::Explosion(const Game* window, const Animation &animation, const sf::Vector2f& position, const float &angle, const float &radius)
    : Entity(window, "Explosion", animation, position, angle, radius)
{}

/**
 * Updates Explosion Object.
 * Does nothing - but must be implemented since Entity is abstract class.
 */
void Explosion::update()
{
	Entity::update();
}
