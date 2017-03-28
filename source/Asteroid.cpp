
#include "Entity.h"
#include "Asteroid.h"


/**
 * Initializes Asteroid Object
 * @param animation object animation
 * @param x x - axis position
 * @param y y - axis position
 * @param angle direction angle
 * @param radius asteroid radius
 */
Asteroid::Asteroid(const Game* window, const Animation &animation, const sf::Vector2f& position, const float &angle, const float &radius)
        : Entity(window, "Asteroid", animation, position, angle, radius)
{
    mVelocity.x = static_cast<float>(rand() % 8 - 4);
	mVelocity.y = static_cast<float>(rand() % 8 - 4);
}

/**
 * Updates Asteroid position.
 */
void Asteroid::update()
{
	Entity::update();

	move(mVelocity);

	if (getPosition().x > 1200.F) setPosition(0, getPosition().y);
    if (getPosition().x < 0.F) setPosition(1200, getPosition().y);
    if (getPosition().y > 800.F) setPosition(getPosition().x, 0);
    if (getPosition().y < 0.F) setPosition(getPosition().x, 800);
}
