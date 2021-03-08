# Stickman
* **Extensions:** the extensions present in this implementation
* **Structure:** the overarching structure of the code base
* **Classes:** a brief rundown of each class involved
* **Design Patterns:** a discussion of the design pattern used
* **Config File:** the options present in the config file
* **Style:** the styleguide used.

## Extensions
The first extension present is pause functionality. Pressing the Tab
key will prevent the game from playing and will display a relevant overlay.
This details how to quit (Esc) and unpause (Tab).

The second and significantly larger extension is the presence of
randomly placed eye-candy as part of the background. These are broken into
2 main categories: air and ground. The ground objects are the most simple,
having a constant y position amongst them and moving at the same speed
as the background. Their placements are constantly being randomly generated
so as to keep it interesting. The air objects operate the same way but
move twice as fast and have a random y position (changing every occurance)
near the top of the screen. Their positions and the textures used are
configurable via the config file. Adding a new texture to either list
will make it appear as part of the rotation with no extra work or
recompilation required.

## Structure
The structure of the code base has been broken down into a couple of key
components. The Dialog class operates as the game manager, existing at the
very top level, containing references to everything else and propogating
things like painting events. Below it is the Player class which
deals with things related to our stickman, albeit very limited
at this stage. Alongside this is the world manager class which handles
the objects that exist in our world. This has a factory to produce our
world objects (background tiles or eyecandy) as well as a list of the ones
produced. It handles the updates to all of these at every frame.

There is an interesting feature of the Factory present. The sprites used to create
our world objects are reused via pointers to prevent creating a unique instance for
each. As such, they have to be persisted throughout the lifetime of the program
exterior to the world objects themselves. This is done via the factory that produces
them - it exists as a member of the WorldManager and its lifetime is tied to the
WorldManager which is in turn tied to Dialog and thus the whole application.
This is a little bit weird as typically the produced objects should be independant
once spawned. The alternative, however, is to duplicate resources by giving a unique
texture to each which is not desirable OR to create an auxilary class to store these
sprites. This would operate in the exact same way and would have the same lifetime
issues and strange dependencies while also further convoluting the design. As such,
neither of these options are any better and thus not pursued.

## Classes
There are a lot of classes present so this details quickly the purpose behind each.

* **Background:** Implement WorldObject as a background panel
* **Config:** Read and store the info present in the config file
* **Dialog:** Game manager to handle high level events
* **Eyecandy:** Implement WorldObject as an eyecandy instance (air or ground)
* **Player:** Handle everthing related to the stickman
* **Position:** Store the position and dimensions of an object
* **WorldManager:** Handle events on a lower level, maintaining all world objects
* **WorldObject:** Abstract class for objects in our world
* **WorldObjectFactory:** Create different types of world objects

There is also a header.h file which contains a few basic #defines to prevent
the presence of magic numbers throughout the code.

## Design Patterns
The only pattern currently present is a Factory Method to create the
different types of WorldObject instances. The Background and Eyecandy classes
implement the pure virtual functions of the WorldObject abstract class.
The WorldObjectFactory then has a method which takes an enum and an additional
parameter, creating and returning the relevant WorldObject implementation.
This simplifies the creation and management of these objects which currently
make up the vast majority of components.

No creational pattern is used for the other main classes: WorldManager and Player.
Both have lifetimes tied to the application and very simple construction.
There is therefore nothing to be gained and using a creational design pattern
would generally only serve to complicate things. The other helper classes,
Position and Config, also do not have a construction patterns for similar reasons -
they are sufficiently simple and/or once-off that using a pattern would only
serve to complicate the process of using them.

## Config Options
The config file contains a large number of different tunable parameters which
are detailed below:


* **size:** The size of the player ("tiny", "normal", "large", "huge")
* **initX:** The initial x position of the player
* **initY:**  The initial y position of the player
* **velocity:**  The velocity of the player
* **backgroundTexture:** The texture used for the background
* **playerTexture:** The texture used for the player
* **pauseTexture:** The texture used for the pause overlay
* **airCandyTextures:** A list of textures for the air eyecandy objects
* **groundCandyTextures:** A list of textures for the ground eyecandy objects
* **airCandyPosition:** The min y position of the air eyecandy
* **groundCandyPosition:** The y position of the ground eyecandy

All textures are given as paths to the relevant file. These are relative to the
executable itself in the build folder. A default set are included and will
be automatically copied into the build folder when the project is built.

## Style
The styleguide for this project follows the
[google C++ style guide](https://google.github.io/styleguide/cppguide.html),
with the following changes and/or highlighted features:

* Soft tabs of size 4
* Opening brace never on its own line - should be at the end of the line that caused it
* Closing brace on its own line
* Braces should NOT be used for control expressions containing only a single line
* Functions and control expressions should be on a single line when the
  content is short (e.g. getter functions, `else return false`, etc.)
* Camelcase naming - Capitalised first letter for classes, lowercase for variables
* Typically every block of code (generally max ~8 lines unless very repetitive), block of
  declaractions (in header file) or function implementation should have a brief comment explaining it
* No code should be in header files - put it all in the relevant .cpp file
* Single line whitespace should be used extensively to distinguish between sections
