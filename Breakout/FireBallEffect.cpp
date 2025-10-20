#include "FireBallEffect.h"

#include "Ball.h"

FireBallEffect::FireBallEffect(Ball* ball) :_ball{ ball }
{
}

void FireBallEffect::ApplyEffect(float duration)
{
	BaseEffect::ApplyEffect(duration);
	_ball->setFireBall(true);
}

void FireBallEffect::EndEffect()
{
	_ball->setFireBall(false);
}

BaseEffect* FireBallEffect::CopyEffect()
{
	return new FireBallEffect(_ball);
}