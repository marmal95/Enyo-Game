
#include "Entity.h"
#include "Asteroid.h"


/**
 * Initializes Asteroid Object
 * @param animation object animation
 * @param x x - axis position
 * @param y y - axis position
 * @param angle direction angle
 * @param radius asteroid radius
 */
Asteroid::Asteroid(const Game* window, const Animation &animation, const int &x, const int &y, const float &angle, const float &radius)
        : Entity(window, "Asteroid", animation, x, y, angle, radius)
{
    dx = static_cast<float>(rand() % 8 - 4);
    dy = static_cast<float>(rand() % 8 - 4);
}

/**
 * Updates Asteroid position.
 */
void Asteroid::update()
{
    this->x_pos += dx;
    this->y_pos += dy;

    if (x_pos > 1200.F) x_pos = 0.F;
    if (x_pos < 0.F) x_pos = 1200.F;
    if (y_pos > 800.F) y_pos = 0.F;
    if (y_pos < 0.F) y_pos = 800.F;
}
