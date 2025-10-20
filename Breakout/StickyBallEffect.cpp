#include "StickyBallEffect.h"

#include "Ball.h"

StickyBallEffect::StickyBallEffect(Ball* ball) :_ball{ ball }
{
}

void StickyBallEffect::ApplyEffect(float duration)
{
	BaseEffect::ApplyEffect(duration);

	_ball->setSticky(true);
}

void StickyBallEffect::EndEffect()
{
	_ball->setSticky(false);
}

BaseEffect* StickyBallEffect::CopyEffect()
{
	return new StickyBallEffect(_ball);
}
