#include "PowerupContainer.h"

#include "CONSTANTS.h"

PowerupContainer::PowerupContainer(sf::RenderWindow* window, sf::Color color) :_window{ window }, _color{ color }, _velocity{ 0,250.f },_shouldBeDestroyed{false}
{
	_sprite.setRadius(POWERUP_RADIUS);
	_sprite.setFillColor(color);
}

PowerupContainer::PowerupContainer(PowerupContainer& first) 
	:_window{ first._window },_color{first._color},_velocity{first._velocity}
	,_sprite{first._sprite}
{
	//Copy effects (uses custom function that circumvents copy constructor limitations)
	for (std::unique_ptr<IEffect>& effect : first._effects)
	{
		_effects.emplace_back(effect->CopyEffect());
	}
}

void PowerupContainer::AddEffect(IEffect* effect)
{
	_effects.emplace_back(effect);
}

void PowerupContainer::Update(float dt)
{
	_sprite.move(_velocity * dt);

	//TODO: Handle collision with player in player
	
	//Flag for destruction once object should be destroyed
	if (_sprite.getPosition().y + _sprite.getRadius() * 2 >= _window->getSize().y)
	{
		_shouldBeDestroyed = true;
	}
}

void PowerupContainer::Render()
{
	_window->draw(_sprite);
}

void PowerupContainer::ApplyEffect()
{
	for (std::unique_ptr<IEffect>& effect : _effects)
	{
		effect->ApplyEffect(2.0f);
	}
}
