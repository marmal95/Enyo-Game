#ifndef ENYO_ANIMATION_H
#define ENYO_ANIMATION_H

#include <SFML/Graphics/Sprite.hpp>
#include <vector>

class Animation
{
private: // TODO: private
    float frame;
    float speed;
    sf::Sprite sprite;
    std::vector<sf::IntRect> frames;

public:
    Animation();
    Animation(const sf::Texture &t, const sf::Vector2f& position,
              const int &w, const int &h, const int &count, const float &speed);
    ~Animation();
    void setSpritePos(const float& x_pos, const float& y_pos);
    void setSpriteRot(const float& rot);
	const sf::Sprite& getSprite() const;

    void update();
    bool finished();
};

#endif //ENYO_ANIMATION_H
