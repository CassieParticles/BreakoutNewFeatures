#include "Effects.h"

#include <iostream>

#include "Paddle.h"
#include "Ball.h"

void IEffect::UpdateEffect(float dt)
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
	IEffect::ApplyEffect(duration);
	std::cout << _debugMessage << '\n';
}

IEffect* DebugEffect::CopyEffect()
{
	return new DebugEffect(_debugMessage);
}

PaddleSizeEffect::PaddleSizeEffect(Paddle* paddle, float _paddleSizeMultiplier) :paddle{ paddle },_paddleSizeMultiplier{_paddleSizeMultiplier}
{}

void PaddleSizeEffect::ApplyEffect(float duration)
{
	IEffect::ApplyEffect(duration);
	paddle->setWidth(_paddleSizeMultiplier, duration);
}

void PaddleSizeEffect::EndEffect()
{
	paddle->setWidth(1/_paddleSizeMultiplier, 0.0f);
}


IEffect* PaddleSizeEffect::CopyEffect()
{
	return new PaddleSizeEffect(paddle, _paddleSizeMultiplier);
}

BallSpeedEffect::BallSpeedEffect(Ball* ball, float ballSpeedMultiplier):ball{ball},ballSpeedMultiplier{ballSpeedMultiplier}
{}

void BallSpeedEffect::ApplyEffect(float duration)
{
	IEffect::ApplyEffect(duration);
	ball->setVelocity(ballSpeedMultiplier, duration);
}

void BallSpeedEffect::EndEffect()
{
	ball->setVelocity(1 / ballSpeedMultiplier, 0.0f);
}

IEffect* BallSpeedEffect::CopyEffect()
{
	return new BallSpeedEffect(ball, ballSpeedMultiplier);
}
