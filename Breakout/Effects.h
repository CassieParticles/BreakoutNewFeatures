#pragma once

#include <string>

class Paddle;
class Ball;

//Interface
class IEffect
{
public:
	virtual void ApplyEffect(float duration) = 0;

	//Used in factory pattern (copy constructor doesn't want to play ball)
	virtual IEffect* CopyEffect() = 0; 
};

class DebugEffect : public IEffect
{
public:
	DebugEffect(const std::string& debugMessage = "Hello, World!");
	std::string debugMessage;

	void ApplyEffect(float duration) override;
	IEffect* CopyEffect();
};

class PaddleSizeEffect : public IEffect
{
public:
	PaddleSizeEffect(Paddle* paddle, float paddleSizeMultiplier = 1.0f);
	
	void ApplyEffect(float duration) override;
	IEffect* CopyEffect();
private:
	Paddle* paddle;
	float paddleSizeMultiplier;
};

class BallSpeedEffect : public IEffect
{
public:
	BallSpeedEffect(Ball* ball, float ballSpeedMultiplier = 1.0f);

	void ApplyEffect(float duration) override;
	IEffect* CopyEffect();
private:
	Ball* ball;
	float ballSpeedMultiplier;
};