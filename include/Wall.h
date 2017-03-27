#ifndef ENYO_WALL_H
#define ENYO_WALL_H

#include "Entity.h"
#include "Animation.h"
#include "Game.h"

class Wall : public Entity
{
public:
	Wall(const Game* window, const Animation &animation, const int &x, const int &y, const float &angle = 1, const float &sizeX = 1);
	void update() override;
};

#endif // !ENYO_WALL