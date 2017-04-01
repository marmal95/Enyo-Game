#pragma once

#include <SFML/Graphics/RenderTarget.hpp>

#include "SceneNode.h"
#include "Animation.h"

#include <string>

#ifndef M_PI
constexpr float M_PI = 3.141592F;
#endif // !M_PI

class GamePlay;

class Entity : public SceneNode
{
protected:
	sf::Vector2f mVelocity;
    float radius;
    bool life;
    std::string name;
    Animation anim;

    const GamePlay* window;

public:
    Entity(const GamePlay* window, const std::string& name, const Animation& animation,
          const sf::Vector2f& position, const float& angle = 0, const float& radius = 1);
    ~Entity();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void update() override;

	void setVelocity(const sf::Vector2f& velocity);
	void setVelocity(float dx, float dy);
	sf::Vector2f getVelocity() const;

    float getRadius() const;
    bool getLife() const;
    Animation& getAnimation();
    const std::string& getName() const;
    void setAnimation(const Animation& animation);
    void setLife(bool life);
};
