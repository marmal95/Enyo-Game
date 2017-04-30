#ifndef ENYO_WALL_H
#define ENYO_WALL_H

#include "Entity.h"
#include "Animation.h"

class Wall : public Entity
{
public:
	Wall(const GamePlay* window, const Animation& animation, const Vector<float>& position,
		const float& angle, const float& sizeX);
	void update(float dt) override;
};

#endif // !ENYO_WALL