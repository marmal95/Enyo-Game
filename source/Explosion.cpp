#include "Explosion.h"

/**
 * Initializes Explosion Object
 * @param animation object animation
 * @param x x - axis position
 * @param y y - axis position
 * @param angle direction angle
 * @param radius object radius
 */
Explosion::Explosion(const Animation& animation, const Vector<float>& position, const float& angle, const float& radius)
	: Entity(animation, position, angle, radius)
{
	id = EntityId::Explosion;
}

/**
 * Updates Explosion Object.
 * Does nothing - but must be implemented since Entity is abstract class.
 */
void Explosion::update(float dt)
{
	Entity::update(dt);
}
