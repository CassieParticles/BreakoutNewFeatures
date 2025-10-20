#pragma once
#include <SFML/Graphics.hpp>


class GameManager;  // forward declaration



class Ball {
public:
    Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager);
    ~Ball();
    void update(float dt);
    void render();
    void setVelocity(float coeff);
    void setFireBall(bool fireball);
    void setSticky(bool sticky); 
    void setGodmode(bool isGodmode);
    void setSize(float coeff);

private:
    sf::CircleShape _sprite;
    sf::Vector2f _direction;
    sf::RenderWindow* _window;
    float _velocity;
    bool _isAlive;
    bool _isFireBall;
    bool _isSticky;
    bool _isGodmode;

    bool _isStuck;
    sf::Vector2f _stuckDirection;

    GameManager* _gameManager;  // Reference to the GameManager


    static constexpr float RADIUS = 10.0f;      
    static constexpr float VELOCITY = 350.0f;   // for reference.
};

