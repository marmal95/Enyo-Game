#pragma once
#include "ResourceHolder.hpp"
#include "Id.h"
#include "Animation.h"
#include "Entity.h"
#include "Player.h"
#include "MapGenerator.h"
#include "GameStage.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <list>

class GamePlay : public GameStage
{
private:
	// Game Dimension
	sf::Vector2i worldDimension;

	// Camera
	sf::View mWorldView;

	//Map generator
	MapGenerator generator;

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
	void addWalls();

	void createPlayer();
	void createAsteroids(const uint32_t& count);
	void createSmallAsteroids(const uint32_t& count);

	void checkPlayerMove();
	void checkCollisions();
	void checkUpdateEntities();
	void checkSounds();

	bool isCollide(const Entity* const a, const Entity* const b);

public:
	GamePlay(sf::RenderWindow& window, const sf::Vector2i& dimension);

	virtual void init() override;
	virtual bool update(float dt) override;
	virtual void draw(sf::RenderWindow &window) override;
	virtual void release() override;
	virtual void handleUserInput(sf::Keyboard::Key key, bool pressed) override;

	sf::Vector2i getDimension() const;
};