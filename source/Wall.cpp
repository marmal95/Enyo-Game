#include "Wall.h"

/**
 * Initializes Wall object
 * @param window window we draw on
 * @param animation wall animation - if exists
 * @param position wall position
 * @param angle wall rotation angle
 * @param sizeX wall size
 */
Wall::Wall(const Animation& animation, const Vector<float>& position, const float& angle, const float& sizeX)
	: Entity(animation, position, angle, sizeX)
{
	id = EntityId::Wall;
}

/**
 * Updates Wall object.
 */
void Wall::update(float dt)
{
	Entity::update(dt);
}