#include "PowerupContainer.h"

#include "CONSTANTS.h"

PowerupContainer::PowerupContainer(sf::RenderWindow* window, sf::Color color) :window{ window }, color{ color }, velocity{ 0,250.f },shouldBeDestroyed{false}
{
	sprite.setRadius(POWERUP_RADIUS);
	sprite.setFillColor(color);
}

PowerupContainer::PowerupContainer(PowerupContainer& first) 
	:window{ first.window },color{first.color},velocity{first.velocity}
	,sprite{first.sprite}
{
	//Copy effects (uses custom function that circumvents copy constructor limitations)
	for (std::unique_ptr<IEffect>& effect : first.effects)
	{
		effects.emplace_back(effect->CopyEffect());
	}
}

void PowerupContainer::AddEffect(IEffect* effect)
{
	effects.emplace_back(effect);
}

void PowerupContainer::Update(float dt)
{
	sprite.move(velocity * dt);

	//TODO: Handle collision with player in player
	// 
	//TODO: Handle destruction when hitting floor
}

void PowerupContainer::Render()
{
	window->draw(sprite);
}

void PowerupContainer::ApplyEffect()
{
	for (std::unique_ptr<IEffect>& effect : effects)
	{
		effect->ApplyEffect(5.0f);
	}
}
