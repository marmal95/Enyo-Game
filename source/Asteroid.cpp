
#include <cmath>
#include <iostream>
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
Asteroid::Asteroid(const GamePlay* window, const Animation& animation, const sf::Vector2f& position, const float& angle, const float& radius)
	: Entity(window, animation, position, angle, radius)
{
	id = EntityId::Asteroid;

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
