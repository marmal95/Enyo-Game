#pragma once
#include "ResourceHolder.hpp"
#include "Id.h"
#include "Animation.h"
#include "Entity.h"
#include "Player.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <list>

class World
{
private:
	sf::Vector2i worldDimension;
	sf::RenderWindow& mWindow;
	sf::View mWorldView;

	// Texture Holder
	ResourceHolder<sf::Texture, ID> mTextureHolder;

	// Animation Holder
	ResourceHolder<Animation, ID> mAnimationHolder;

	// Sound Holder
	ResourceHolder<sf::SoundBuffer, ID> mSoundHolder;

	// Sounds
	std::list<sf::Sound> qSounds;

	// Entities List
	std::list<std::unique_ptr<Entity>> entities;

	// Background Sprite
	sf::Sprite sBackground;

	// Pointer to Player Aircraft
	Player* playerAircraft;

private:
	void initializeWold();
	void buildScene();

	void createPlayer();
	void createAsteroids(const uint32_t& count);
	void createSmallAsteroids(const uint32_t& count);

	void checkPlayerMove();
	void checkCollisions();
	void checkUpdateEntities();
	void checkSounds();

	bool isCollide(const Entity* const a, const Entity* const b);

public:
	World(sf::RenderWindow& window, const sf::Vector2i& dimension);
	void processEvents();
	void update();
	void draw();

	sf::Vector2i getDimension() const;
};