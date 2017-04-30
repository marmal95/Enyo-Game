#ifndef ENYO_ANIMATION_H
#define ENYO_ANIMATION_H

#include <SFML/Graphics/Sprite.hpp>
#include <vector>

#include "Vector.hpp"

class Animation
{
private:
    float frame;
    float speed;
    sf::Sprite sprite;
    std::vector<sf::IntRect> frames;

public:
	Animation();
	Animation(const sf::Texture &t, const Vector<float>& position,
              const int& w, const int& h, const int& count, const float& speed);

    void setSpritePos(const float& x_pos, const float& y_pos);
    void setSpriteRot(const float& rot);

	const sf::Sprite& getSprite() const;

    void update();
    bool finished();
};

#endif //ENYO_ANIMATION_H
