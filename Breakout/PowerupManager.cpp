#include "PowerupManager.h"

#include <iostream>


PowerupManager::PowerupManager(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
    : _window(window), _paddle(paddle), _ball(ball)
{
    InitialisePowerups();
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
    //Pick random powerup from vector
    int randomNumber = rand() % templatePowerups.size();
    PowerupContainer* randomPowerup = templatePowerups[randomNumber];

    //Copy random powerup
    PowerupContainer* powerup = new PowerupContainer(*randomPowerup);
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

void PowerupManager::InitialisePowerups()
{
    PowerupContainer* fastBall = new PowerupContainer(_window, sf::Color::Yellow);
    PowerupContainer* slowBall = new PowerupContainer(_window, sf::Color::Blue);
    PowerupContainer* bigPaddle = new PowerupContainer(_window, sf::Color(155,0,255));
    PowerupContainer* smallPaddle = new PowerupContainer(_window, sf::Color::Green);
    PowerupContainer* fireBall = new PowerupContainer(_window, sf::Color::Red);

    fastBall->AddEffect(new BallSpeedEffect(_ball, 2.0f));
    slowBall->AddEffect(new BallSpeedEffect(_ball, 0.5f));
    bigPaddle->AddEffect(new PaddleSizeEffect(_paddle, 1.5f));
    smallPaddle->AddEffect(new PaddleSizeEffect(_paddle, 0.67f));
    fireBall->AddEffect(new DebugEffect("Fireball totally implemented :P"));

    templatePowerups.push_back(fastBall);
    templatePowerups.push_back(slowBall);
    templatePowerups.push_back(bigPaddle);
    templatePowerups.push_back(smallPaddle);
    templatePowerups.push_back(fireBall);
}