#include "Asteroid.h"
#include "Explosion.h"
#include "Bullet.h"
#include "Wall.h"

#include <SFML/Window/Event.hpp>
#include <cmath>

#include <iostream>

/**
 * Initializes GamePlay
 * @param window window we play on
 * @param dimension window dimension
 */
GamePlay::GamePlay(sf::RenderWindow& window, const sf::Vector2i& dimension)
        : worldDimension(dimension), mWorldView(window.getDefaultView()),
          mTextureHolder(), mAnimationHolder(), mSoundHolder(),
          qSounds(), entities(), sBackground(),
          generator(39, 24, "z", 1)
{}

/**
 * Initializes GamePlay.
 */
void GamePlay::init()
{
    initializeWold();
    buildScene();
    addWalls();
}

/**
 * Updates Game logic
 * @param dt frame time
 * @return true - if keep updating, false - otherwise
 */
bool GamePlay::update(float dt)
{
    checkPlayerMove();
    checkCollisions();
    checkUpdateEntities();
    checkSounds();

    return true;
}

/**
 * Draws Game objects on screen.
 * @param window window we draw on
 */
void GamePlay::draw(sf::RenderWindow& window)
{

    mWorldView.setCenter(playerAircraft->getPosition());
    window.setView(mWorldView);

    // Draw Background
    window.draw(sBackground);

    // Draw all entities
    for (const auto& i : entities)
        window.draw(*i);
}

/**
 * Releases allocated resources
 */
void GamePlay::release()
{
    // Nothing to release.
}

/**
 * Handles user input
 * @param key key pressed by user
 * @param pressed true - if pressed, false - if released
 */
void GamePlay::handleUserInput(sf::Keyboard::Key key, bool pressed)
{
    switch (key)
    {
        case sf::Keyboard::Space:
            if (pressed)
            {
                entities.push_back(
                        std::make_unique<Bullet>(this, mAnimationHolder.getResource(ID::BulletBlue),
                                                 sf::Vector2f(playerAircraft->getPosition().x,
                                                              playerAircraft->getPosition().y),
                                                 playerAircraft->getRotation(), 10.F));
                qSounds.push_back(sf::Sound(mSoundHolder.getResource(ID::BulletBlueSound)));
                qSounds.back().play();
            }
            break;

        default:
            break;
    }
}

/**
 * Get game dimension
 * @return game dimension
 */
sf::Vector2i GamePlay::getDimension() const
{
    return worldDimension;
}

/**
 * Initializes Game world. Loads resources.
 */
void GamePlay::initializeWold()
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

    mAnimationHolder.load(ID::Explosion,
                          std::make_unique<Animation>(mTextureHolder.getResource(ID::Explosion), sf::Vector2f(0, 0),
                                                      256, 256, 48, 0.5));
    mAnimationHolder.load(ID::RockBig,
                          std::make_unique<Animation>(mTextureHolder.getResource(ID::RockBig), sf::Vector2f(0, 0), 64,
                                                      64, 16, 0.2));
    mAnimationHolder.load(ID::RockSmall,
                          std::make_unique<Animation>(mTextureHolder.getResource(ID::RockSmall), sf::Vector2f(0, 0), 64,
                                                      64, 16, 0.2));
    mAnimationHolder.load(ID::BulletBlue,
                          std::make_unique<Animation>(mTextureHolder.getResource(ID::BulletBlue), sf::Vector2f(0, 0),
                                                      32, 64, 16, 0.8));
    mAnimationHolder.load(ID::Spaceship,
                          std::make_unique<Animation>(mTextureHolder.getResource(ID::Spaceship), sf::Vector2f(40, 0),
                                                      40, 40, 1, 0));
    mAnimationHolder.load(ID::SpaceshipFly, std::make_unique<Animation>(mTextureHolder.getResource(ID::SpaceshipFly),
                                                                        sf::Vector2f(40, 40), 40, 40, 1, 0));
    mAnimationHolder.load(ID::ExplosionShip,
                          std::make_unique<Animation>(mTextureHolder.getResource(ID::ExplosionShip), sf::Vector2f(0, 0),
                                                      192, 192, 64, 0.5));
    mAnimationHolder.load(ID::Wall,
                          std::make_unique<Animation>(mTextureHolder.getResource(ID::Wall), sf::Vector2f(0, 0), 50, 50,
                                                      1, 0));

    mSoundHolder.load(ID::BigExplosionSound, "sounds/explosion_big.wav");
    mSoundHolder.load(ID::SmallExplosionSound, "sounds/explosion_small.wav");
    mSoundHolder.load(ID::BulletBlueSound, "sounds/laser_blue.wav");
}

/**
 * Builds game scene. Player, enemies etc...
 */
void GamePlay::buildScene()
{
    // Create Map
    // ...

    // Create Player
    createPlayer();

    // Create Bigger Asteroids in Random positions
    createAsteroids(15);

    // Create Smaller Asteroids in Random positions
    createSmallAsteroids(5);
}

/**
 * Creates walls
 */
void GamePlay::addWalls()
{
    for (int i = 0; i < 24; ++i)
        for (int j = 0; j < 39; ++j)
            if (generator.getField(static_cast<uint32_t>(j), static_cast<uint32_t>(i)) == MapField::Wall)
                entities.push_back(
                        std::make_unique<Wall>(this, mAnimationHolder.getResource(ID::Wall),
                                               sf::Vector2f(static_cast<float>(j * 50), static_cast<float>(i * 50)), 0,
                                               25));
}

/**
 * Creates Player's aircraft
 */
void GamePlay::createPlayer()
{
    auto player = std::make_unique<Player>(this, mAnimationHolder.getResource(ID::Spaceship), generator.getStartPoint(),
                                           0.F, 20.F);
    playerAircraft = player.get();
    entities.push_back(std::move(player));
}

/**
 * Creates Asteroids
 * @param count number of asteroids to create
 */
void GamePlay::createAsteroids(const uint32_t& count)
{
    float x, y;
    for (uint32_t i = 0; i < count; ++i)
    {
        x = static_cast<float>(rand() % worldDimension.x);
        y = static_cast<float>(rand() % worldDimension.y);
        //to be sure that asteroid will not hit wall
        if (generator.isEmpty(x, y) && generator.isEmpty(x - 25.F, y - 25.F) && generator.isEmpty(x, y - 25.F) &&
            generator.isEmpty(x + 25.F, y - 25.F) && generator.isEmpty(x - 25.F, y) && generator.isEmpty(x + 25.F, y) &&
            generator.isEmpty(x + 25.F, y + 25.F) && generator.isEmpty(x, y + 25.F) &&
            generator.isEmpty(x - 25.F, y + 25.F))
            entities.push_back(
                    std::make_unique<Asteroid>(this, mAnimationHolder.getResource(ID::RockBig),
                                               sf::Vector2f(x, y), static_cast<float>(rand() % 360), 25.F));
        else
            --i;//to create count asteroids
    }
}

/**
 * Creates small Asteroids
 * @param count number of asteroids to create
 */
void GamePlay::createSmallAsteroids(const uint32_t& count)
{
    float x, y;
    for (uint32_t i = 0; i < count; ++i)
    {
        x = static_cast<float>(rand() % worldDimension.x);
        y = static_cast<float>(rand() % worldDimension.y);
        //to be sure that asteroid will not hit wall
        if (generator.isEmpty(x, y) && generator.isEmpty(x - 25.F, y - 25.F) && generator.isEmpty(x, y - 25.F) &&
            generator.isEmpty(x + 25.F, y - 25.F) && generator.isEmpty(x - 25.F, y) && generator.isEmpty(x + 25.F, y) &&
            generator.isEmpty(x + 25.F, y + 25.F) && generator.isEmpty(x, y + 25.F) &&
            generator.isEmpty(x - 25.F, y + 25.F))
            entities.push_back(
                    std::make_unique<Asteroid>(this, mAnimationHolder.getResource(ID::RockSmall),
                                               sf::Vector2f(x, y), static_cast<float>(rand() % 360), 15.F));
        else
            --i;//to create count asteroids
    }
}

/**
 * Checks if players wants to move
 */
void GamePlay::checkPlayerMove()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) playerAircraft->rotate(3);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) playerAircraft->rotate(-3);
    playerAircraft->setMoving(sf::Keyboard::isKeyPressed(sf::Keyboard::Up));

    if (playerAircraft->isMoving())
        playerAircraft->setAnimation(mAnimationHolder.getResource(ID::SpaceshipFly));
    else
        playerAircraft->setAnimation(mAnimationHolder.getResource(ID::Spaceship));
}

/**
 * Checks Entities collisions.
 */
void GamePlay::checkCollisions()
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
                if (a->getRadius() > 20)
                    qSounds.push_back(sf::Sound(mSoundHolder.getResource(ID::BigExplosionSound)));
                else
                    qSounds.push_back(sf::Sound(mSoundHolder.getResource(ID::SmallExplosionSound)));
                qSounds.back().play();

                entities.push_back(std::make_unique<Explosion>(this, mAnimationHolder.getResource(ID::Explosion),
                                                               sf::Vector2f(a->getPosition().x, a->getPosition().y)));

                for (int i = 0; i < 2; i++)
                {
                    if (a->getRadius() == 15)
                        break;
                    entities.push_back(
                            std::make_unique<Asteroid>(this, mAnimationHolder.getResource(ID::RockSmall),
                                                       sf::Vector2f(a->getPosition().x, a->getPosition().y),
                                                       rand() % 360, 15));
                }
            }
            else if (a->getName() == "Player" && b->getName() == "Asteroid" && isCollide(a.get(), b.get()))
            {
                b->setLife(false);
                entities.push_back(std::make_unique<Explosion>(this, mAnimationHolder.getResource(ID::ExplosionShip),
                                                               sf::Vector2f(a->getPosition().x, a->getPosition().y)));

                qSounds.push_back(sf::Sound(mSoundHolder.getResource(ID::BigExplosionSound)));
                qSounds.back().play();

                    playerAircraft->setPosition(200, 200);
                   playerAircraft->setVelocity(0, 0);
            }
            else if (a->getName() == "Player" && b->getName() == "Wall" && isCollide(a.get(), b.get()))
            {
                entities.push_back(std::make_unique<Explosion>(this, mAnimationHolder.getResource(ID::ExplosionShip),
                                                               sf::Vector2f(a->getPosition().x, a->getPosition().y)));

                qSounds.push_back(sf::Sound(mSoundHolder.getResource(ID::BigExplosionSound)));
                qSounds.back().play();

                    playerAircraft->setPosition(200, 200);
                   playerAircraft->setVelocity(0, 0);
            }
            else if (a->getName() == "Asteroid" && b->getName() == "Wall" && isCollide(a.get(), b.get()))
            {
                // Current Velocity Vector
                float vX = a->getVelocity().x;
                float vY = a->getVelocity().y;

                // Velocity Vector Norm
                float vLen = static_cast<float>(sqrt(vX*vX+vY*vY));

                // Normal Line
                float nX = b->getPosition().x - a->getPosition().x;
                float nY = b->getPosition().y - a->getPosition().y;

                // Normalize N - vector
                float nLen = static_cast<float>(sqrt(nX * nX + nY * nY));
                nX /= nLen;
                nY /= nLen;

                // V * N - dot product
                float dotProd_VN = vX * nX + vY * nY;

                // New V vector
                float nVX = vX - 2 * dotProd_VN * nX;
                float nVY = vY - 2 * dotProd_VN * nY;

                // Reflection Angle
                float refAngle = static_cast<float>(acos(dotProd_VN / (vLen * nLen)));
                refAngle *= 2 * 180./M_PI;

                // Bounce and Rotate
            //    a->rotate(refAngle);
                a->setVelocity(nVX, nVY);
            }
            else if (a->getName() == "Bullet" && b->getName() == "Wall" && isCollide(a.get(), b.get()))
            {
                a->setLife(false);
            }
        }
    }
}

/**
 * Updates Entities and their animation. Remove them if not alive.
 */
void GamePlay::checkUpdateEntities()
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
 * Checks Game sounds. If stopped playing - remove them.
 */
void GamePlay::checkSounds()
{
    auto end = qSounds.end();
    for (auto i = qSounds.begin(); i != end;)
    {
        if (i->getStatus() == sf::Sound::Stopped)
            i = qSounds.erase(i);
        else
            ++i;
    }
}

/**
 * Checks if there was collision between two entities
 * @param a first entity
 * @param b second entity
 * @return true - if there was collision, false - otherwise
 */
bool GamePlay::isCollide(const Entity* const a, const Entity* const b)
{
    return (b->getPosition().x - a->getPosition().x) * (b->getPosition().x - a->getPosition().x) +
           (b->getPosition().y - a->getPosition().y) * (b->getPosition().y - a->getPosition().y) <
           (a->getRadius() + b->getRadius()) * (a->getRadius() + b->getRadius());
}
