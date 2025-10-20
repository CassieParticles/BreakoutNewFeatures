#include "GodModeEffect.h"

#include "Ball.h"

GodModeEffect::GodModeEffect(Ball* ball):_ball{ball}
{
}

void GodModeEffect::ApplyEffect(float duration)
{
	BaseEffect::ApplyEffect(duration);
	_ball->setGodmode(true);
}

void GodModeEffect::EndEffect()
{
	_ball->setGodmode(false);
}

BaseEffect* GodModeEffect::CopyEffect()
{
	return new GodModeEffect(_ball);
}
