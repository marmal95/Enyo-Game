#pragma once

#include "Entity.h"

class Asteroid : public Entity
{
public:
    Asteroid(const Animation& animation, const Vector<float>& position,
		const float& angle, const float& radius);
    void update(float dt) override;
};
