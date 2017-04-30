
#ifndef ENYO_EXPLOSION_H
#define ENYO_EXPLOSION_H

#include "Entity.h"

class Explosion : public Entity
{
public:
    Explosion(const GamePlay* window, const Animation& animation, const Vector<float>& position,
              const float& angle, const float& radius);
    void update(float dt) override;
};

#endif //ENYO_EXPLOSION_H
