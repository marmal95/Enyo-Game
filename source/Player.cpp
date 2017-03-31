#include "Player.h"
#include "GamePlay.h"

#include <iostream>

/**
 * Initializes Player Data
 * @param animation player animation
 * @param x x - axis position
 * @param y y - axis position
 * @param angle direction angle
 * @param radius player radius
 */
Player::Player(const GamePlay* window, const Animation &animation, const sf::Vector2f& position, const float &angle, const float &radius)
        : Entity(window, "Player", animation, position, angle, radius)
{}

/**
 * Updates Player Position.
 */
void Player::update()
{
	Entity::update();

    if (moving)
    {
        mVelocity.x += static_cast<float>(cos(getRotation() * M_PI/180.) * 0.2);
		mVelocity.y += static_cast<float>(sin(getRotation() * M_PI/180.) * 0.2);
    } else
    {
		mVelocity.x *= 0.99F;
		mVelocity.y *= 0.99F;
    }

    // TODO: Set max speed to entity
    // TODO: And allow entities to have acceleration
    int maxSpeed = 15;
    float speed = static_cast<float>(sqrt(mVelocity.x * mVelocity.x + mVelocity.y * mVelocity.y));

    if (speed > maxSpeed)
    {
		mVelocity.x *= maxSpeed / speed;
		mVelocity.y *= maxSpeed / speed;
    }

	move(mVelocity);

 //   if (getPosition().x > window->getDimension().x) setPosition(0, getPosition().y);
	//if (getPosition().x < 0.F) setPosition(window->getDimension().x, getPosition().y);
	//if (getPosition().y > window->getDimension().y) setPosition(getPosition().x, 0);
 //   if (getPosition().y < 0.F) setPosition(getPosition().x, window->getDimension().y);

	// Debug
	if (getPosition().y < 0 || getPosition().y >= window->getDimension().y)
		mVelocity.y = -mVelocity.y;
	if (getPosition().x < 0 || getPosition().x >= window->getDimension().x)
		mVelocity.x = -mVelocity.x;
}

bool Player::isMoving() const
{
    return moving;
}

void Player::setMoving(bool moving)
{
    this->moving = moving;
}
