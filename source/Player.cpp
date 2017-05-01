#include "Player.h"
#include "GamePlay.h"

#include <cmath>

/**
 * Initializes Player Data
 * @param animation player animation
 * @param x x - axis position
 * @param y y - axis position
 * @param angle direction angle
 * @param radius player radius
 */
Player::Player(const Animation& animation, const Vector<float>& position, const float& angle, const float& radius)
	: Entity(animation, position, angle, radius)
{
	id = EntityId::Player;
}

/**
 * Updates Player Position.
 */
void Player::update(float dt)
{
	Entity::update(dt);

	if (moving)
	{
		mVelocity.x += static_cast<float>(cos(getRotation() * M_PI / 180.) * 0.2);
		mVelocity.y += static_cast<float>(sin(getRotation() * M_PI / 180.) * 0.2);
	}
	else
	{
		mVelocity.x *= 0.99F;
		mVelocity.y *= 0.99F;
	}

	int maxSpeed = 15;
	float speed = static_cast<float>(sqrt(mVelocity.x * mVelocity.x + mVelocity.y * mVelocity.y));

	if (speed > maxSpeed)
	{
		mVelocity.x *= maxSpeed / speed;
		mVelocity.y *= maxSpeed / speed;
	}

	move(mVelocity);
}

/**
 * Return if player is moving
 * @return true - if player is moving, false - otherwise
 */
bool Player::isMoving() const
{
	return moving;
}

/**
 * Sets if player is moving
 * @param moving true - if is moving, false - otherwise
 */
void Player::setMoving(bool moving)
{
	this->moving = moving;
}
