
#include "Game.h"
#include "Menu.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Explosion.h"
#include "Wall.h"

#include <SFML/Window/Event.hpp>

#include <iostream>

// TODO: Pozycje -> Vector2f ??

/**
 * Initializes Game Window
 * @param w window width
 * @param h width height
 */
Game::Game(const uint32_t& w, const uint32_t& h)
        :
        width(w), height(h), app(sf::VideoMode(w, h), "The Enyo Game"),
        mTextureHolder(), mAnimationHolder(), mSoundHolder(),
        sBackground(), qSounds(), entities()
{
    app.setFramerateLimit(60);

    showMenu();
}

/**
 * Displays StartUp Menu. Runs game or exits.
 */
void Game::showMenu()
{
    Menu menu(app, width, height);
    int choice = menu.getSelectedOption();
    if (choice == 0)
        initializeGame();
    else
        app.close();
}

/**
 * Gets player reference.
 * @return player reference
 */
std::unique_ptr<Player>& Game::player()
{
    return (std::unique_ptr<Player>&) entities.front();
}

/**
 * Initializes textures and sprites. Creates Player and Objects. Runs game.
 */
void Game::initializeGame()
{
    mTextureHolder.load(ID::Explosion, "images/type_C.png");
    mTextureHolder.load(ID::RockBig, "images/rock.png");
    mTextureHolder.load(ID::RockSmall, "images/rock_small.png");
    mTextureHolder.load(ID::BulletBlue, "images/fire_blue.png");
    mTextureHolder.load(ID::Spaceship, "images/spaceship.png", true);
    mTextureHolder.load(ID::SpaceshipFly, "images/spaceship.png");
    mTextureHolder.load(ID::ExplosionShip, "images/type_B.png");
    mTextureHolder.load(ID::SpaceBackground, "images/background.jpg", true);
	mTextureHolder.load(ID::Wall, "images/wall.png");

    sBackground.setTexture(mTextureHolder.getResource(ID::SpaceBackground));

    mAnimationHolder.load(ID::Explosion, std::make_unique<Animation>(mTextureHolder.getResource(ID::Explosion), 0, 0, 256, 256, 48, 0.5));
    mAnimationHolder.load(ID::RockBig, std::make_unique<Animation>(mTextureHolder.getResource(ID::RockBig), 0, 0, 64, 64, 16, 0.2));
    mAnimationHolder.load(ID::RockSmall, std::make_unique<Animation>(mTextureHolder.getResource(ID::RockSmall), 0, 0, 64, 64, 16, 0.2));
    mAnimationHolder.load(ID::BulletBlue, std::make_unique<Animation>(mTextureHolder.getResource(ID::BulletBlue), 0, 0, 32, 64, 16, 0.8));
    mAnimationHolder.load(ID::Spaceship, std::make_unique<Animation>(mTextureHolder.getResource(ID::Spaceship), 40, 0, 40, 40, 1, 0));
    mAnimationHolder.load(ID::SpaceshipFly, std::make_unique<Animation>(mTextureHolder.getResource(ID::SpaceshipFly), 40, 40, 40, 40, 1, 0));
    mAnimationHolder.load(ID::ExplosionShip, std::make_unique<Animation>(mTextureHolder.getResource(ID::ExplosionShip), 0, 0, 192, 192, 64, 0.5));
	mAnimationHolder.load(ID::Wall, std::make_unique<Animation>(mTextureHolder.getResource(ID::Wall), 0, 0, 50, 50, 1, 0));

    mSoundHolder.load(ID::BigExplosionSound, "sounds/explosion_big.wav");
    mSoundHolder.load(ID::SmallExplosionSound, "sounds/explosion_small.wav");
    mSoundHolder.load(ID::BulletBlueSound, "sounds/laser_blue.wav");

    createPlayer();
 //   createAsteroids(15);
 //   createSmallAsteroids(5);

	createOutline();

    run();
}

/**
 * Add outline of walls
 */

void Game::createOutline()
{
	for(int i = 0; i <= width/50; ++i)
	{
		entities.push_back(std::make_unique<Wall>(this, mAnimationHolder.getResource(ID::Wall), i * 50, 0, 0, 25));
		entities.push_back(std::make_unique<Wall>(this, mAnimationHolder.getResource(ID::Wall), i * 50, 800, 0, 25));
	}
	for (int i = 0; i <= height / 50; ++i)
	{
		entities.push_back(std::make_unique<Wall>(this, mAnimationHolder.getResource(ID::Wall), 0, i * 50, 0, 25));
		entities.push_back(std::make_unique<Wall>(this, mAnimationHolder.getResource(ID::Wall), 1200, i * 50, 0, 25));
	}
}

/**
 * Creates Player.
 */
void Game::createPlayer()
{
    auto player = std::make_unique<Player>(this, mAnimationHolder.getResource(ID::Spaceship), 200, 200, 0, 20);
    entities.push_back(std::move(player));
}

/**
 * Creates Asteroids.
 * @param count number of asteroids
 */
void Game::createAsteroids(const uint32_t& count)
{
    for (uint32_t i = 0; i < count; ++i)
    {
        entities.push_back(
                std::make_unique<Asteroid>(this, mAnimationHolder.getResource(ID::RockBig), rand() % width, rand() % height, rand() % 360, 25));
    }
}


/**
 * Creates Small Asteroids.
 * @param count number of asteroids
 */
void Game::createSmallAsteroids(const uint32_t& count)
{
    for (uint32_t i = 0; i < count; ++i)
        entities.push_back(
                std::make_unique<Asteroid>(this, mAnimationHolder.getResource(ID::RockSmall), rand() % width, rand() % height, rand() % 360, 15));
}

/**
 * Checks collisions between Entities.
 * @param a first entity
 * @param b second entity
 * @return true - if there was collision, false - otherwise
 */
bool Game::isCollide(const Entity* const a, const Entity* const b)
{
	if (a->getName() == "Wall")
	{
		float circleDistX = abs(b->getXPos() - a->getXPos());
		float circleDistY = abs(b->getYPos() - a->getYPos());
		
		if(circleDistX > (a->getRadius()/2 + b->getRadius()))
			return false;
		if(circleDistY > (a->getRadius()/2 + b->getRadius()))
			return false;

		if(circleDistX <= (a->getRadius() / 2))
			return true;
		if (circleDistY <= (a->getRadius() / 2))
			return true;

		float cornerDistance = (circleDistX - a->getRadius()/2)*(circleDistX - a->getRadius() / 2) +
								(circleDistY - a->getRadius() / 2)*(circleDistY - a->getRadius() / 2);
		return (cornerDistance <= b->getRadius()*b->getRadius());
	}
	else
		return (b->getXPos() - a->getXPos()) * (b->getXPos() - a->getXPos()) +
			   (b->getYPos() - a->getYPos()) * (b->getYPos() - a->getYPos()) <
			   (a->getRadius() + b->getRadius()) * (a->getRadius() + b->getRadius());
}

/**
 * Main Game Loop. Handles events, updates logic and renders objects.
 */
void Game::run()
{
    while (app.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

/**
 * Handles User Input
 */
void Game::processEvents()
{
    sf::Event event;
    while (app.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            app.close();

        if (event.type == sf::Event::KeyPressed)
            if (event.key.code == sf::Keyboard::Space)
            {
                entities.push_back(
                        std::make_unique<Bullet>(this, mAnimationHolder.getResource(ID::BulletBlue), player()->getXPos(),
                                                 player()->getYPos(), player()->getAngle(), 10));
                qSounds.push_back(sf::Sound(mSoundHolder.getResource(ID::BulletBlueSound)));
                qSounds.back().play();
            }
    }
}

/**
 * Updates Game Logic
 */
void Game::update()
{
    checkPlayerMove();
    checkCollisions();
    checkUpdateEntities();
    checkSounds();
}

/**
 * Renders Game
 */
void Game::render()
{
    app.clear();

    app.draw(sBackground);
    for (const auto& i:entities)
        i->draw(app);

    app.display();
}

/**
 * Checks if player should move.
 */
void Game::checkPlayerMove()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) player()->addAngle(3);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) player()->subAngle(3);
    player()->setMoving(sf::Keyboard::isKeyPressed(sf::Keyboard::Up));

    if (player()->isMoving())
        player()->setAnimation(mAnimationHolder.getResource(ID::SpaceshipFly));
    else
        player()->setAnimation(mAnimationHolder.getResource(ID::Spaceship));
}

/**
 * Checks if there is any collision between some entities.
 */
void Game::checkCollisions()
{
    for (auto& a : entities)
    {
        for (auto& b : entities)
        {
            if (a->getName() == "Asteroid" && b->getName() == "Bullet" && isCollide(a.get(), b.get()))
            {
                a->setLife(false);
                b->setLife(false);

                // Play Sound
                if(a->getRadius() > 20)
                    qSounds.push_back(sf::Sound(mSoundHolder.getResource(ID::BigExplosionSound)));
                else
                    qSounds.push_back(sf::Sound(mSoundHolder.getResource(ID::SmallExplosionSound)));
                qSounds.back().play();

                entities.push_back(std::make_unique<Explosion>(this, mAnimationHolder.getResource(ID::Explosion), a->getXPos(), a->getYPos()));

                for (int i = 0; i < 2; i++)
                {
                    if (a->getRadius() == 15)
                        break;
                    entities.push_back(
                            std::make_unique<Asteroid>(this, mAnimationHolder.getResource(ID::RockSmall), a->getXPos(), a->getYPos(), rand() % 360, 15));
                }
            }
			else if (a->getName() == "Player" && b->getName() == "Asteroid" && isCollide(a.get(), b.get()))
            {
                b->setLife(false);
                entities.push_back(std::make_unique<Explosion>(this, mAnimationHolder.getResource(ID::ExplosionShip), a->getXPos(), a->getYPos()));

                qSounds.push_back(sf::Sound(mSoundHolder.getResource(ID::BigExplosionSound)));
                qSounds.back().play();

                player()->setData(mAnimationHolder.getResource(ID::Spaceship), width / 2, height / 2, 0, 20);
                player()->setDx(0);
                player()->setDy(0);
            }
			else if (a->getName() == "Player" && b->getName() == "Wall" && isCollide(a.get(), b.get()))
			{
				entities.push_back(std::make_unique<Explosion>(this, mAnimationHolder.getResource(ID::ExplosionShip), a->getXPos(), a->getYPos()));

				qSounds.push_back(sf::Sound(mSoundHolder.getResource(ID::BigExplosionSound)));
				qSounds.back().play();

				player()->setData(mAnimationHolder.getResource(ID::Spaceship), width / 2, height / 2, 0, 20);
				player()->setDx(0);
				player()->setDy(0);
			}
        }
    }
}

/**
 * Updates entities moves and animations.
 */
void Game::checkUpdateEntities()
{
    auto end = entities.end();
    for (auto i = entities.begin(); i != end;)
    {
        // Get Entity
        auto e = i->get();

        // Update Move
        e->update();

        // Update Animation
        e->getAnimation().update();

        // Remove Explosion if finished playing
        if (e->getName() == "Explosion" && e->getAnimation().finished())
            e->setLife(0);

        // Erase dead objects
        if (!e->getLife())
            i = entities.erase(i);
        else
            ++i;
    }
}

/**
 * Checks if sound finished playing. If yes - erares it from list.
 */
void Game::checkSounds()
{
    auto end = qSounds.end();
    for(auto i = qSounds.begin(); i != end;)
    {
        if (i->getStatus() == sf::Sound::Stopped)
            i = qSounds.erase(i);
        else
            ++i;
    }
}

/**
 * Returns window width
 * @return window width
 */
uint32_t Game::getWidth() const
{
    return width;
}

/**
 * Returns window height
 * @return window height
 */
uint32_t Game::getHeight() const
{
    return height;
}
