#include "Effects.h"

#include <iostream>

#include "Paddle.h"
#include "Ball.h"

DebugEffect::DebugEffect(const std::string& debugMessage) :debugMessage{ debugMessage }
{
}

void DebugEffect::ApplyEffect(float duration)
{
	std::cout << debugMessage << '\n';
}

IEffect* DebugEffect::CopyEffect()
{
	return new DebugEffect(debugMessage);
}

PaddleSizeEffect::PaddleSizeEffect(Paddle* paddle, float paddleSizeMultiplier) :paddle{ paddle },paddleSizeMultiplier{paddleSizeMultiplier}
{}

void PaddleSizeEffect::ApplyEffect(float duration)
{
	paddle->setWidth(paddleSizeMultiplier, duration);
}

IEffect* PaddleSizeEffect::CopyEffect()
{
	return new PaddleSizeEffect(paddle, paddleSizeMultiplier);
}

BallSpeedEffect::BallSpeedEffect(Ball* ball, float ballSpeedMultiplier):ball{ball},ballSpeedMultiplier{ballSpeedMultiplier}
{}

void BallSpeedEffect::ApplyEffect(float duration)
{
	ball->setVelocity(ballSpeedMultiplier, duration);
}

IEffect* BallSpeedEffect::CopyEffect()
{
	return new BallSpeedEffect(ball, ballSpeedMultiplier);
}
