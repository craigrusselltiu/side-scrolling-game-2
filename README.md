# Stickman
* **Extensions:** the extensions present in this implementation
* **Structure:** the overarching structure of the code base
* **Classes:** a brief rundown of each class involved
* **Design Patterns:** a discussion of the design pattern used
* **Config File:** the options present in the config file

## What I Learned
- Working and extending existing code bases
- Using design patterns to add new functionalities to already existing code
- Among other things!

## Extensions
The first extension allows the player to double jump by pressing spacebar
again while in the air.

The second, considrably larger extension sometimes makes an obstacle more
powerful/harder to pass. For the given obstacles, there is a 20% chance that it
gains an aura, which basically makes the obstacle larger. There is also a 20% chance
that the obstacle moves up and down on the Y axis. Finally, there is a 10% chance
that both of these "powers" are given to the obstacle, creating a much bigger
moving obstacle.

## Structure
The structure of the initial stage 1 code is maintained, with a world manager that
handles all the world objects. The functionality of the previous stage is also preserved,
and can be run in the config file. Now, it also handles the updating of the obstacles,
adding and removing them whenever necessary, i.e. when the last placed obstacle
has passed the distance specified by the config file, or when the obstacle leaves
the screen.

There is now an obstacle object which implements the world object interface. The
obstacles are created through the existing object factory created by the original code.
These are then added to the world objects container in the world manager accordingly.
Collision is checked for in every frame by drawing two rectangles to create
hitboxes of the player and the obstacles respectively. The QRect intersects() function
is then used on both hitboxes to check if the player hitbox has intersected an
obstacle hitbox, prompting the game to stop.

## Classes
Apart from the classes highlighted in the first README, here are the ones added in stage 2:

* **Obstacle:** Implements WorldObject. Obstacles for the game.
* **Decorator:** Interface for the decorators.
* **AuraDecorator:** Decorator that increases the size of the obstacle.
* **MoveDecorator:** Decorator that prompts the obstacle to move up and down.

There is also a header.h file which contains a few basic #defines to prevent
the presence of magic numbers throughout the code.

## Design Patterns
The only additional design pattern added is the Decorator structural design pattern.
This is used to augment the obstacles, adding interesting enhancements to them
that make them harder to pass.

## Config Options
In addition to the initial config options, here are the ones added in stage 2:

* **stage:** Initialises appropriate stage behaviour
* **testMode:** True/False - enables testing mode
* **gravity:** The gravity of the player, i.e. when jumping
* **jumpVelocity:** The upwards velocity when jumping
* **obstacleSizeX:** The width of the obstacles
* **obstacleSizeY:** The height of the obstacles
* **obstacleDistance:** The distance between obstacles
* **obstacleVelocity:** The speed at which an augmented obstacle goes up and down
* **obstacleEdgeDistance:** The distance from the edges the obstacle should stop at
						 *  when moving up and down
* **obstacleTextures:** The texture selection for obstacles, i.e. colour
* **obstacleSequence:** The sequence of Y values to place the obstacles at


The remaining unexplained options are simply alternate textures to give the game a different
look in feel for stage 2.
