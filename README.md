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
10 min - Fixed circular dependency

3 1/2 hrs - Refactored and overhauled powerup system, remanaged object responsibilities
Powerups now work on a composition based system, where powerups can be made up using effects, effects can be created by making a class inherit from the BaseEffect and overriding the virtual member functions (ApplyEffect, EndEffect, CopyEffect, GetName)
ApplyEffect needs to call the BaseEffect ApplyEffect function and CopyEffect needs to return a new identical copy of the effect. EndEffect needs to fully reverse what ApplyEffect did, so if ApplyEffect added 1 to ball size, EndEffect needs to subtract 1
Adding new powerups is done in the powerupManager InitialisePowerups function, define a new PowerupContainer, add the effects wanted using the AddEffect function, then add the new powerup to the templatePowerups vector, new powerups will be selected from that vector
Powerups and effects are managed by the PowerupManager, spawning powerups are created by cloning a powerup from the template vector.
The UI displaying powerups now displays active effects, this displays the name given by GetName, and how long that effect will run for, this can display multiple effects simultaneously

I chose to make this change to reduce the need for shotgun surgery within the project whenever a new powerup is added. This is a problem as it increases the implementation time of new powerups being added, which reduces the amount of iteration that can be done. 
It also runs the problem of a developer forgetting to change any of the specific systems that require updating, introducing new bugs that could be avoided. Additionally, all the systems were built to only have one active powerup at a time, which means if a 
designer wanted the player to have multiple active powerups, they couldn't.

Overall the new system is designed to be more usable for adding new powerups and effects, and reduce the responsibilities of other systems to keep up to date with the current powerups

30 minutes - Added new powerups
Paddle speed - Increase or decrease the speed of the paddle
Sticky ball - Ball sticks to the paddle, press space to launch it
Godmode - Ball acts as fireball + cannot lose lives

