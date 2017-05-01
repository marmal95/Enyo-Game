#include "Bullet.h"
#include "GamePlay.h"

#include <cmath>

/**
 * Initializes Bullet Object.
 * @param animation bullet animation
 * @param x x - axis position
 * @param y y - axis position
 * @param angle direction move angle
 * @param radius bullet radius
 */
Bullet::Bullet(const Animation& animation, const Vector<float>& position, const float& angle, const float& radius)
	: Entity(animation, position, angle, radius)
{
	id = EntityId::Bullet;

	mVelocity.x = static_cast<float>(cos(angle * M_PI / 180.) * 12);
	mVelocity.y = static_cast<float>(sin(angle * M_PI / 180.) * 12);
}

/**
 * Updates Bullet position.
 */
void Bullet::update(float dt)
{
	Entity::update(dt);
	move(mVelocity);
}
