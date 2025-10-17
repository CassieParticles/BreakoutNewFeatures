#pragma once

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Effects.h"

#include "CONSTANTS.h"

class PowerupContainer
{
public:
	PowerupContainer(sf::RenderWindow* window, sf::Color color);
	PowerupContainer(PowerupContainer& first);
	//Set up
	void SetPosition(sf::Vector2f position);

	//Powerup lifecycle
	void AddEffect(IEffect* effect);
	void Update(float dt);
	void Render();
	void ApplyEffect();

	//Checks
	void CheckCollisionWithPaddle(Paddle* paddle);
	bool ShouldBeDestroyed() { return _shouldBeDestroyed; }
private:
	//Rendering
	sf::RenderWindow* _window;
	sf::CircleShape _sprite;
	sf::Color _color;

	sf::Vector2f _velocity;

	std::vector<std::unique_ptr<IEffect>> _effects;

	bool _shouldBeDestroyed;
};