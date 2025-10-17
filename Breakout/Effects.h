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

	virtual std::string GetName() { return "Default effect name"; }

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

	std::string GetName() override { return "Debug"; }

	IEffect* CopyEffect();
};

class PaddleSizeEffect : public IEffect
{
public:
	PaddleSizeEffect(Paddle* paddle, float _paddleSizeMultiplier = 1.0f);
	
	void ApplyEffect(float duration) override;
	void EndEffect();

	std::string GetName() override { return "Paddle size"; }

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

	std::string GetName() override { return "Ball speed"; }

	IEffect* CopyEffect();
private:
	Ball* ball;
	float ballSpeedMultiplier;
};

class FireBallEffect : public IEffect
{
public:
	FireBallEffect(Ball* ball);

	void ApplyEffect(float duration) override;
	void EndEffect();

	std::string GetName() override { return "Fire ball"; }

	IEffect* CopyEffect();
private:
	Ball* _ball;
};