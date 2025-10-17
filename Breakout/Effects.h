#pragma once

#include <string>

class Paddle;
class Ball;

//Not really an interface anymore
class IEffect
{
public:
	virtual void ApplyEffect(float duration) { _durationLeft = duration; }
	virtual void EndEffect() = 0;

	virtual void UpdateEffect(float dt);

	virtual IEffect* CopyEffect() = 0; 

	bool ShouldBeDestroyed() { return _shouldBeDestroyed; }
	float getDurationLeft() { return _durationLeft; }

private:
	float _durationLeft;
	bool _shouldBeDestroyed;
};

class DebugEffect : public IEffect
{
public:
	DebugEffect(const std::string& _debugMessage = "Hello, World!");
	std::string _debugMessage;

	void ApplyEffect(float duration) override;
	void EndEffect() {}


	IEffect* CopyEffect();
};

class PaddleSizeEffect : public IEffect
{
public:
	PaddleSizeEffect(Paddle* paddle, float _paddleSizeMultiplier = 1.0f);
	
	void ApplyEffect(float duration) override;
	void EndEffect();


	IEffect* CopyEffect();
private:
	Paddle* paddle;
	float _paddleSizeMultiplier;
};

class BallSpeedEffect : public IEffect
{
public:
	BallSpeedEffect(Ball* ball, float ballSpeedMultiplier = 1.0f);

	void ApplyEffect(float duration) override;
	void EndEffect();


	IEffect* CopyEffect();
private:
	Ball* ball;
	float ballSpeedMultiplier;
};