#include "PowerupManager.h"

#include <iostream>


PowerupManager::PowerupManager(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
    : _window(window), _paddle(paddle), _ball(ball)
{
    templateContainer = new PowerupContainer(_window, sf::Color::Red);
    templateContainer->AddEffect(new DebugEffect("Effect applied"));
    templateContainer->AddEffect(new BallSpeedEffect(_ball, 0.2f));
}

PowerupManager::~PowerupManager()
{
    for (auto powerup : _powerups)
    {
        delete powerup;
    }
    _powerups.clear();
}

void PowerupManager::update(float dt)
{


    // tick down powerup effect time. Reset if elapsed.
    if (_powerupInEffect)
    {
        _powerupInEffect->second -= dt;
        if (_powerupInEffect->second <= 0)
        {
            _powerupInEffect.reset();
        }
    }

    for (auto it = powerups.begin(); it != powerups.end();)
    {
        (*it)->Update(dt);
        if ((*it)->ShouldBeDestroyed())
        {
            delete *it;
            it = powerups.erase(it);
        }
        else
        {
            ++it;
        }
    }


    //for (auto it = _powerups.begin(); it != _powerups.end(); )
    //{
    //    checkCollision();
    //    
    //    // Delete powerups queued for removal
    //    (*it)->update(dt);
    //    if (!(*it)->isAlive())
    //    {
    //        delete* it;
    //        it = _powerups.erase(it);
    //    }
    //    else
    //    {
    //        ++it;
    //    }
    //}
}

void PowerupManager::render()
{
    for (auto& powerup : _powerups)
    {
        powerup->render();
    }
    for (auto& powerup : powerups)
    {
        powerup->Render();
    }
}

void PowerupManager::spawnPowerup()
{
    //TODO: Add powerup spawning

    powerups.push_back(new PowerupContainer(*templateContainer));
}

void PowerupManager::checkCollision()
{
    for (auto& powerup : _powerups)
    {

        if (powerup->checkCollisionWithPaddle())
        {
            _powerupInEffect = powerup->applyEffect();
            powerup->setAlive(false);
        }
    }
}

int PowerupManager::getPowerupsSpawned()
{
    return _powerups.size();
}

std::pair<POWERUPS, float> PowerupManager::getPowerupInEffect()
{
    if (!_powerupInEffect) return { none, 0.f };
    return *_powerupInEffect;
}
