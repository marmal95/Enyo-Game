
#include "Entity.h"
#include "Player.h"
#include "Game.h"

/**
 * Initializes Player Data
 * @param animation player animation
 * @param x x - axis position
 * @param y y - axis position
 * @param angle direction angle
 * @param radius player radius
 */
Player::Player(const Game* window, const Animation &animation, const int &x, const int &y, const float &angle, const float &radius)
        : Entity(window, "Player", animation, x, y, angle, radius)
{}

/**
 * Updates Player Position.
 */
void Player::update()
{
    if (moving)
    {
        dx += static_cast<float>(cos(angle * M_PI/180.) * 0.2);
        dy += static_cast<float>(sin(angle * M_PI/180.) * 0.2);
    } else
    {
        dx *= 0.99F;
        dy *= 0.99F;
    }

    // TODO: Set max speed to entity
    // TODO: And allow entities to have acceleration
    int maxSpeed = 15;
    float speed = static_cast<float>(sqrt(dx * dx + dy * dy));

    if (speed > maxSpeed)
    {
        dx *= maxSpeed / speed;
        dy *= maxSpeed / speed;
    }

    x_pos += dx;
    y_pos += dy;

    if (x_pos > window->getWidth()) x_pos = 0.F;
    if (x_pos < 0.F) x_pos = static_cast<float>(window->getWidth());
    if (y_pos > window->getHeight()) y_pos = 0.F;
    if (y_pos < 0.F) y_pos = static_cast<float>(window->getHeight());
}

bool Player::isMoving() const
{
    return moving;
}

void Player::setMoving(bool moving)
{
    this->moving = moving;
}
