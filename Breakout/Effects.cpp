#include "Effects.h"

#include <iostream>

#include "Paddle.h"
#include "Ball.h"

void BaseEffect::UpdateEffect(float dt)
{
	_durationLeft -= dt;

	if (_durationLeft < 0)
	{
		EndEffect();
		_shouldBeDestroyed = true;
	}
}


DebugEffect::DebugEffect(const std::string& _debugMessage) :_debugMessage{ _debugMessage }
{
}

void DebugEffect::ApplyEffect(float duration)
{
	BaseEffect::ApplyEffect(duration);
	std::cout << _debugMessage << '\n';
}

FireBallEffect::FireBallEffect(Ball* ball):_ball{ball}
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

BaseEffect* DebugEffect::CopyEffect()
{
	return new DebugEffect(_debugMessage);
}

PaddleSizeEffect::PaddleSizeEffect(Paddle* paddle, float _paddleSizeMultiplier) :paddle{ paddle },_paddleSizeMultiplier{_paddleSizeMultiplier}
{}

void PaddleSizeEffect::ApplyEffect(float duration)
{
	BaseEffect::ApplyEffect(duration);
	paddle->setWidth(_paddleSizeMultiplier);
}

void PaddleSizeEffect::EndEffect()
{
	paddle->setWidth(1/_paddleSizeMultiplier);
}


BaseEffect* PaddleSizeEffect::CopyEffect()
{
	return new PaddleSizeEffect(paddle, _paddleSizeMultiplier);
}

BallSpeedEffect::BallSpeedEffect(Ball* ball, float ballSpeedMultiplier):ball{ball},ballSpeedMultiplier{ballSpeedMultiplier}
{}

void BallSpeedEffect::ApplyEffect(float duration)
{
	BaseEffect::ApplyEffect(duration);
	ball->setVelocity(ballSpeedMultiplier);
}

void BallSpeedEffect::EndEffect()
{
	ball->setVelocity(1.0f / ballSpeedMultiplier);
}

BaseEffect* BallSpeedEffect::CopyEffect()
{
	return new BallSpeedEffect(ball, ballSpeedMultiplier);
}
