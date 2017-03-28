
#ifndef ENYO_GAMEWINDOW_H
#define ENYO_GAMEWINDOW_H

#ifndef M_PI
	constexpr float M_PI = 3.141592F;
#endif // !M_PI


#include "ResourceHolder.hpp"
#include "Animation.h"
#include "Entity.h"
#include "Player.h"
#include "Id.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/View.hpp>

#include <list>
#include <memory>
#include <queue>


class Game
{
private:
    uint32_t width;
    uint32_t height;
    sf::RenderWindow app;

    // Texture Holder
    ResourceHolder<sf::Texture, ID> mTextureHolder;

    // Animation Holder
    ResourceHolder<Animation, ID> mAnimationHolder;

    // Sound Holder
    ResourceHolder<sf::SoundBuffer, ID> mSoundHolder;

    // Sound
    std::list<sf::Sound> qSounds;

    // Background Sprite
    sf::Sprite sBackground;

    // Entities List
    std::list<std::unique_ptr<Entity>> entities;

	// View
	sf::View view;

private:
    void showMenu();


    void createPlayer();

    void createAsteroids(const uint32_t& count);

    void createSmallAsteroids(const uint32_t& count);

	void createOutline();


    void checkPlayerMove();

    void checkCollisions();

    void checkUpdateEntities();

    void checkSounds();


    bool isCollide(const Entity* const a, const Entity* const b);

    void initializeGame();


    void run();

    void processEvents();

    void update();

    void render();

    std::unique_ptr<Player>& player();

public:
    Game(const uint32_t& width, const uint32_t& height);
    uint32_t getWidth() const;
    uint32_t getHeight() const;
};

#endif //ENYO_GAMEWINDOW_H
