#pragma once

#include "Entity.h"

class Wall : public Entity
{
public:
	Wall(const Animation& animation, const Vector<float>& position,
		const float& angle, const float& sizeX);
	void update(float dt) override;
};