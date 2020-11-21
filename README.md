# Hero's Journey

## Group information
- **Group Number**: 15
- **Name**: Kwok Ka Yan    **UID**: 3035705336
- **Name**: Choi Tsz Long  **UID**: 3035705154
## OS Environment
- Runs Natively on X2Go HKU Linux Servers!
## Game description
Genre: role-playing and puzzle 
- The player solves a series of puzzles, finally reaching the boss room where the final battle takes place. 
### Story
Set in a fictional world, the young Hero has been chosen to fight the Demon King, who has taken their father's life. Before embarking on his quest, the Elders entrusted the Hero with the Three Commandments:
- First, do no harm.
- Second, reach the Golden Plate.
- Third, kill the Demon King.\
The Hero enters the Demon King's lair and must complete the trials to reach the Throne Room.
## Basic game rules
- In the puzzles, the player must push around boulders and avoid obstacles to get to the exit. 
- There are pressure plates that can be activated by the player, mobs and objects like a boulder, which can unlock other objects (a door) in the game.
- Mobs move in random ways, or follow the player around.
- The player takes damage when he moves adjacent to a mob. When mobs moves adjacent to the player, the player also takes damage.
- When the player's health points drop to zero, the game reverts to the main menu. 
- The player can only "kill" the final boss and must use the environment to his advantage for his defence.
### Default controls
- w, a, s and d for movement (only lowercase)
- H/h for game menu (for restarting, save/load, quit game and return to main menu)
- In all menus, the controls are printed at the left. Both uppercase and lowercase input will work!
## Features to implement
This section shall cover the features, catergorized by the **code requirement** items 1 to 5, and others
### Generation of random game sets or events
- The Zombie mob moves randomly.
- The Snake mob chooses random valid positions to move to.
### Data structures for storing game status
- a Point class that defines the position and position manipulating functions
- a Object base class that stores the postion, id, and icon of any object. All objects are derived from it.
- a Map class to represent the level, where the origin (0, 0) is topleft of the level.
- a ObjectStack class to represent each tile of the level, as several objects can be on the same tile.
- a Camera class that stores the topleft position(x, y) and the camera's length.
- a Player class that stores the health, position, name of the player (HERO).
- a WinTile class that defines the position of the winning condition.
- an InfoTile class that stores text from a text file and position of access for the player.
- Classes for other mobs and objects.
- a mobQueue vector that stores the processing order of each object after every player move.
### Dynamic memory management
- Since levels can be in different sizes, or include different objects, the map is loaded dynamically.
- Since the number of mobs can fluctuate in a level, mobQueue is also loaded dynamically (vector).
### File input/output
- Saving the game state.
- Loading the game state.
- Loading levels.
- Loading cutscenes and other information.
- Loading the contents of menus (main menu, game menu, save/load menu... )
### Program codes in multiple files
- A main.cpp containing main, which starts the game.
- A gameFunctions header and cpp files for manipulating the data structures and handling the game (i.e. save/load)
- A colorIO header and cpp files for colored text output
- Seperate header and cpp files for each data structure (excluding the mobQueue vector)
### Others
- Level script format for level design, and a script reading function that reads the file and load the level.
