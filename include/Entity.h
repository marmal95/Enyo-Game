#pragma once

#include <SFML/Graphics/RenderTarget.hpp>

#include "Animation.h"
#include "Id.h"

#include <string>

#ifndef M_PI
constexpr float M_PI = 3.141592F;
#endif // !M_PI

class GamePlay;

class Entity : public sf::Drawable, public sf::Transformable
{
protected:
	// Entity's Force
	sf::Vector2f mForce;

	// Entity's Actual Velocity
	sf::Vector2f mVelocity;

	// Entity's Radius
    float radius;

	// Indicates if entity is alive
    bool life;

	// Entity's Id
	EntityId id;

	// Animated Sprite 
    Animation anim;

	// Game Window
    const GamePlay* window;

public:
    Entity(const GamePlay* window, const Animation& animation,
          const sf::Vector2f& position, const float& angle, const float& radius);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void update(float dt);

	void setVelocity(const sf::Vector2f& velocity);
	void setVelocity(float dx, float dy);
	sf::Vector2f getVelocity() const;
	sf::Vector2f& getVelocity();

    float getRadius() const;
	EntityId getId() const;

    Animation& getAnimation();
    void setAnimation(const Animation& animation);

    void setLife(bool life);
	bool getLife() const;
};
