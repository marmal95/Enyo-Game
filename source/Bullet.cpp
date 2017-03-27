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
Bullet::Bullet(const Game* window, const Animation &animation, const int &x, const int &y, const float &angle, const float &radius)
        : Entity(window, "Bullet", animation, x, y, angle, radius)
{}

/**
 * Updates Bullet position.
 */
void Bullet::update()
{
    dx = static_cast<float>(cos(angle * M_PI/180.) * 18);
    dy = static_cast<float>(sin(angle * M_PI/180.) * 18);
    // angle+=rand()%6-3;
    x_pos += dx;
    y_pos += dy;

    if (x_pos > window->getWidth() || x_pos < 0 || y_pos > window->getHeight() || y_pos < 0)
        life = 0;
}
