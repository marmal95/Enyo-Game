#include <cmath>
#include "Bullet.h"
#include "GamePlay.h"

/**
 * Initializes Bullet Object.
 * @param animation bullet animation
 * @param x x - axis position
 * @param y y - axis position
 * @param angle direction move angle
 * @param radius bullet radius
 */
Bullet::Bullet(const GamePlay* window, const Animation& animation, const Vector<float>& position, const float& angle, const float& radius)
	: Entity(window, animation, position, angle, radius)
{
	id = EntityId::Bullet;

	mVelocity.x = static_cast<float>(cos(getRotation() * M_PI / 180.) * 12);
	mVelocity.y = static_cast<float>(sin(getRotation() * M_PI / 180.) * 12);
}

/**
 * Updates Bullet position.
 */
void Bullet::update(float dt)
{
	Entity::update(dt);
	move(mVelocity);

	if (getPosition().x > window->getDimension().x || getPosition().x < 0 || getPosition().y > window->getDimension().y || getPosition().y < 0)
		life = 0;
}
