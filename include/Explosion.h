#pragma once

#include "Entity.h"

class Explosion : public Entity
{
public:
    Explosion(const Animation& animation, const Vector<float>& position,
              const float& angle, const float& radius);
    void update(float dt) override;
};
