
#include "Entity.h"
#include "Asteroid.h"
#include "Game.h"


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

	rotate(3);
	anim.setSpriteRot(getRotation());
	move(mVelocity);

	if (getPosition().x > window->getWidth()) setPosition(0, getPosition().y);
	if (getPosition().x < 0.F) setPosition(window->getWidth(), getPosition().y);
	if (getPosition().y > window->getHeight()) setPosition(getPosition().x, 0);
	if (getPosition().y < 0.F) setPosition(getPosition().x, window->getHeight());
}
