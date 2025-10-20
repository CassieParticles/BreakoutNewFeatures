#include "Ball.h"
#include "GameManager.h" // avoid cicular dependencies
#include <iostream>

Ball::Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager)
    : _window(window), _velocity(velocity), _gameManager(gameManager),
    _isFireBall(false), _isAlive(true), _direction({1,1})
{
    _sprite.setRadius(RADIUS);
    _sprite.setFillColor(sf::Color::Cyan);
    _sprite.setPosition(0, 300);
}

Ball::~Ball()
{
}

void Ball::update(float dt)
{
    if (_isStuck)
    {
        Paddle* paddle = _gameManager->getPaddle();
        _sprite.setPosition(paddle->getPosition() + sf::Vector2f(paddle->getBounds().width / 2, -_sprite.getRadius() / 2 - 5));
        //Stickiness wears off, or player launches with space
        if (!_isSticky || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            _direction = _stuckDirection;
            _stuckDirection = sf::Vector2f(0, 0);
            _isStuck = false;
        }
        return;
    }


    // Fireball effect
    if (_isFireBall)
    {
        // Flickering effect
        int flicker = rand() % 50 + 205; // Random value between 205 and 255
        _sprite.setFillColor(sf::Color(flicker, flicker / 2, 0)); // Orange flickering color
    }

    // Update position with a subtle floating-point error
    _sprite.move(_direction * _velocity * dt);

    // check bounds and bounce
    sf::Vector2f position = _sprite.getPosition();
    sf::Vector2u windowDimensions = _window->getSize();

    // bounce on walls
    if ((position.x >= windowDimensions.x - 2 * _sprite.getRadius() && _direction.x > 0) || (position.x <= 0 && _direction.x < 0))
    {
        _direction.x *= -1;
    }

    // bounce on ceiling
    if (position.y <= 0 && _direction.y < 0)
    {
        _direction.y *= -1;
    }

    // lose life bounce
    if (position.y > windowDimensions.y)
    {
        //Lose life if godmode is false
        if (_isGodmode)
        {
            _direction.y *= -1;
        }
        else
        {      
            _sprite.setPosition(0, 300);
            _direction = { 1, 1 };
            _gameManager->loseLife();
        }

    }

    // collision with paddle
    if (_sprite.getGlobalBounds().intersects(_gameManager->getPaddle()->getBounds()))
    {
        if (_isSticky)
        {
            _isStuck = true;
            _stuckDirection = _direction;
            _stuckDirection.y *= -1;
            _direction = sf::Vector2f(0, 0);
        }
        else
        {
            _direction.y *= -1; // Bounce vertically

            float paddlePositionProportion = (_sprite.getPosition().x - _gameManager->getPaddle()->getBounds().left) / _gameManager->getPaddle()->getBounds().width;
            _direction.x = paddlePositionProportion * 2.0f - 1.0f;

            // Adjust position to avoid getting stuck inside the paddle
            _sprite.setPosition(_sprite.getPosition().x, _gameManager->getPaddle()->getBounds().top - 2 * _sprite.getRadius());
        }
    }

    // collision with bricks
    int collisionResponse = _gameManager->getBrickManager()->checkCollision(_sprite, _direction);
    if (_isFireBall) return; // no collisisons when in fireBall mode.
    if (collisionResponse == 1)
    {
        _direction.x *= -1; // Bounce horizontally
    }
    else if (collisionResponse == 2)
    {
        _direction.y *= -1; // Bounce vertically
    }
}

void Ball::render()
{
    _window->draw(_sprite);
}

void Ball::setVelocity(float coeff)
{
    _velocity*=coeff;
}

void Ball::setFireBall(bool fireball)
{
    _isFireBall = fireball;       
    if(!fireball)
    {
        _sprite.setFillColor(sf::Color::Cyan);  // back to normal colour.
    }
}

void Ball::setSticky(bool sticky)
{
    _isSticky = sticky;
}

void Ball::setGodmode(bool godmode)
{
    _isGodmode = godmode;
}


void Ball::setSize(float coeff)
{
    _sprite.setRadius(_sprite.getRadius() * coeff);
}
