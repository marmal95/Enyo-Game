#include "Wall.h"

Wall::Wall(const Game* window, const Animation &animation, const int &x, const int &y, const float &angle, const float &sizeX)
	: Entity(window, "Wall", animation, x, y, angle, sizeX)
{
}

void Wall::update()
{}