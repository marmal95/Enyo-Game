
#ifndef ENYO_ASTEROID_H
#define ENYO_ASTEROID_H

#include "Entity.h"

class Asteroid : public Entity
{
public:
    Asteroid(const Game* window, const Animation &animation, const int &x, const int &y, const float &angle = 0, const float &radius = 1);
    void update() override;
};

#endif //ENYO_ASTEROID_H
