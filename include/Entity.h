
#ifndef ENYO_ENTITY_H
#define ENYO_ENTITY_H

#include "Animation.h"
#include "SceneNode.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include <string>
#include <memory>

class Game;

class Entity : public SceneNode
{
protected:
	sf::Vector2f mVelocity;
    float radius;
    bool life;
    std::string name;
    Animation anim;

    const Game* window;

public:
    Entity(const Game* window, const std::string& name, const Animation& animation,
          const sf::Vector2f& position, const float& angle = 0, const float& radius = 1);
    ~Entity();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void update() override;

	void setVelocity(const sf::Vector2f& velocity);
	void setVolocity(float dx, float dy);
	sf::Vector2f getVolocity() const;

    float getRadius() const;
    bool getLife() const;
    Animation& getAnimation();
    const std::string& getName() const;
    void setAnimation(const Animation& animation);
    void setLife(bool life);
};

#endif //ENYO_ENTITY_H
