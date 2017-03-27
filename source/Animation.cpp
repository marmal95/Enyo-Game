
#include "Animation.h"

/**
 * Initializes Variables.
 */
Animation::Animation()
    : frame(0), speed(0), sprite(), frames()
{}

/**
 * Initializes Variables
 * @param t animation sprite texture
 * @param x init x position in texture
 * @param y init y position in texture
 * @param w texture width
 * @param h texture height
 * @param count number of frames in texture
 * @param speed animation speed
 */
Animation::Animation(const sf::Texture &t, const int &x, const int &y,
                     const int &w, const int &h, const int &count, const float &speed)
    : frame(0), speed(speed)
{
    for(int i = 0; i < count; ++i)
        frames.push_back(sf::IntRect(x+i*w, y, w, h));

    sprite.setTexture(t);
    sprite.setOrigin(static_cast<float>(w/2), static_cast<float>(h/2));
    sprite.setTextureRect(frames[0]);
}


Animation::~Animation()
{}

void Animation::setSpritePos(const float& x_pos, const float& y_pos)
{
    sprite.setPosition(x_pos, y_pos);
}

void Animation::setSpriteRot(const float& rot)
{
    sprite.setRotation(rot);
}

sf::Sprite& Animation::getSprite()
{
    return sprite;
}

/**
 * Updates the animation.
 */
void Animation::update()
{
    frame += speed;
    if(frame > 0 && frame < frames.size())
        sprite.setTextureRect(frames[static_cast<uint32_t>(frame)]);
//    u_long n = frames.size();
//    if(frame >= n)
//        frame -= n;
//    if(n > 0)
//        sprite.setTextureRect(frames[frame]);
}

/**
 * Checks if animation has finished.
 * @return true - if animation finished, false - otherwise
 */
bool Animation::finished()
{
    return frame+speed >= frames.size();
}