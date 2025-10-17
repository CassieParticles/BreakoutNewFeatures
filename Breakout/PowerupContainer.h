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

	void AddEffect(IEffect* effect);

	void Update(float dt);

	void Render();

	void ApplyEffect();
private:
	//Rendering
	sf::RenderWindow* window;
	sf::CircleShape sprite;
	sf::Color color;

	sf::Vector2f velocity;

	std::vector<std::unique_ptr<IEffect>> effects;
};