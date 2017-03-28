
#ifndef ENYO_EXPLOSION_H
#define ENYO_EXPLOSION_H

#include "Entity.h"

class Explosion : public Entity
{
public:
    Explosion(const Game* window, const Animation &animation, const sf::Vector2f& position,
              const float &angle = 0, const float &radius = 1);
    void update() override ;
};

#endif //ENYO_EXPLOSION_H
