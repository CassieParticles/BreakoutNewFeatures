# Breakout

W Kavanagh & N Merchant. Summer 2024 

## controls

A/D to move the paddle right and left.
P to pause.

## Powerups

big/small paddle (blue)
fast/slow ball (fancy yellow)
fire ball (green)

# Tasklist

## Suggested fixes

* Fix the compiler issues in the code

## Suggested tasks

* Implement mouse input for pad
* Improved VFX (ball trail, paddle hit response, brick particle destruction)
* Better UI (progress bar rather than timer for countdown).
* GameLoop
* Better ball physics (Box2D)
* Leaderboards
* More ball types (e.g., multiball, sticky ball [where you shoot the ball from the paddle every time], tiny ball, big ball, brick-tracking ball)
* Sounds with increasing tone between bounces.
* Implement commentary with calls to an LLM such as LLama

# Time Details and Changelist
12:50-13:00 - Fixed circular dependency

17:00-18:45 - Refactored and overhauled powerup system
Powerups now use separate powerup containers, and effects, containers handle position, movement, triggering, and effects make changes to the game when collected
Powerups can have multiple effects, all effects inherit from the IEffect interface
If designers want a new powerup with unique behaviour, or one with parts of existing behaviour, it is much easier to add now

