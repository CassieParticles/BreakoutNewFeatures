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
    for (PowerupContainer* container : _powerups)
    {
        delete container;
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

    checkPlayerCollision();

    for (auto it = _powerups.begin(); it != _powerups.end();)
    {
        (*it)->Update(dt);
        if ((*it)->ShouldBeDestroyed())
        {
            delete *it;
            it = _powerups.erase(it);
        }
        else
        {
            ++it;
        }
    }

}

void PowerupManager::render()
{
    for (auto& powerup : _powerups)
    {
        powerup->Render();
    }
}

void PowerupManager::spawnPowerup(sf::Vector2f position)
{
    PowerupContainer* powerup = new PowerupContainer(*templateContainer);
    _powerups.push_back(powerup);
    powerup->SetPosition(position);
}

void PowerupManager::checkPlayerCollision()
{
    for (auto& powerup : _powerups)
    {
        powerup->CheckCollisionWithPaddle(_paddle);
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
