
#ifndef ENYO_BULLET_H
#define ENYO_BULLET_H

#include "Entity.h"

class Bullet : public Entity
{
public:
    Bullet(const Game* window, const Animation &animation, const int &x, const int &y, const float &angle = 0, const float &radius = 1);
    void update() override;
};

#endif //ENYO_BULLET_H
