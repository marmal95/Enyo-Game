#include "Bullet.h"
#include "Game.h"

/**
 * Initializes Bullet Object.
 * @param animation bullet animation
 * @param x x - axis position
 * @param y y - axis position
 * @param angle direction move angle
 * @param radius bullet radius
 */
Bullet::Bullet(const World* window, const Animation &animation, const sf::Vector2f& position, const float &angle, const float &radius)
        : Entity(window, "Bullet", animation, position, angle, radius)
{}

/**
 * Updates Bullet position.
 */
void Bullet::update()
{
	Entity::update();

	mVelocity.x = static_cast<float>(cos(getRotation() * M_PI/180.) * 18);
	mVelocity.y = static_cast<float>(sin(getRotation() * M_PI/180.) * 18);
    // angle+=rand()%6-3;
	move(mVelocity);

    if (getPosition().x > window->getDimension().x || getPosition().x < 0 || getPosition().y > window->getDimension().y || getPosition().y < 0)
        life = 0;
}
