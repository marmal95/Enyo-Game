#include "Entity.h"
#include "Asteroid.h"
#include "GamePlay.h"

/**
 * Initializes Asteroid Object
 * @param animation object animation
 * @param x x - axis position
 * @param y y - axis position
 * @param angle direction angle
 * @param radius asteroid radius
 */
Asteroid::Asteroid(const Animation& animation, const Vector<float>& position, const float& angle, const float& radius)
	: Entity(animation, position, angle, radius)
{
	id = radius > 20.f ? EntityId::BigAsteroid : EntityId::SmallAsteroid;

	mVelocity.x = static_cast<float>(rand() % 8 - 4);
	mVelocity.y = static_cast<float>(rand() % 8 - 4);
}

/**
 * Updates Asteroid position.
 */
void Asteroid::update(float dt)
{
	Entity::update(dt);
	move(mVelocity);
}
