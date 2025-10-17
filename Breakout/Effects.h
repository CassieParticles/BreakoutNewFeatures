#pragma once

#include <string>

class Paddle;
class Ball;

//Interface
class IEffect
{
public:
	virtual void ApplyEffect(float duration) = 0;
};

class DebugEffect : public IEffect
{
public:
	DebugEffect(const std::string& debugMessage = "Hello, World!");
	std::string debugMessage;

	void ApplyEffect(float duration) override;
};

class PaddleSizeEffect : public IEffect
{
public:
	PaddleSizeEffect(Paddle* paddle, float paddleSizeMultiplier = 1.0f);
	
	void ApplyEffect(float duration) override;
private:
	Paddle* paddle;
	float paddleSizeMultiplier;
};

class BallSpeedEffect : public IEffect
{
public:
	BallSpeedEffect(Ball* ball, float ballSpeedMultiplier = 1.0f);

	void ApplyEffect(float duration) override;
private:
	Ball* ball;
	float ballSpeedMultiplier;
};