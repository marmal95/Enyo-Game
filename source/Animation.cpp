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
Animation::Animation(const sf::Texture& t, const uint32_t& w, const uint32_t& h, const uint32_t& count, const float& speed)
    : frame(0), speed(speed)
{
    for(uint32_t i = 0; i < count; ++i)
        frames.push_back(sf::IntRect(i * w, 0, w, h));

    sprite.setTexture(t);
    sprite.setOrigin(static_cast<float>(w/2), static_cast<float>(h/2));
    sprite.setTextureRect(frames[0]);
}

void Animation::setSpritePos(const float& x_pos, const float& y_pos)
{
    sprite.setPosition(x_pos, y_pos);
}

void Animation::setSpriteRot(const float& rot)
{
    sprite.setRotation(rot);
}

const sf::Sprite& Animation::getSprite() const
{
    return sprite;
}

/**
 * Updates the animation.
 */
void Animation::update()
{
    frame += speed;

    size_t n = frames.size();
    if(frame >= n)
        frame -= n;
    if(n > 0)
		sprite.setTextureRect(frames[static_cast<uint32_t>(frame)]);
}

/**
 * Checks if animation has finished.
 * @return true - if animation finished, false - otherwise
 */
bool Animation::finished()
{
    return frame+speed >= frames.size();
}