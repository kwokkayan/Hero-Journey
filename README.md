# Untitled Role-playing Puzzle Game

## Group members information
- **Name**: Kwok Ka Yan    **UID**: 3035705336
- **Name**: Choi Tsz Long  **UID**: 3035705154

## Game description
Genre: role-playing and puzzle 
- The player solves a series of puzzles, themed with the 4 seasons of the year - spring(tutorial), summer(quicksand), autumn(matured tall wheat) and winter(blizzard), finally reaching the boss room where the final battle takes place. 
### Story
Set in a fictional world, the young Hero has been chosen to fight the Demon King, who has taken their father's life. Before embarking on his quest, the Elders entrusted the Hero with the Three Commandments:
- First, do no harm.
- Second, go right.
- Third, kill the Demon King.
The Hero enters the Demon King's lair, confronted by Trial of the 4 Seasons, and must complete the trials to reach the Throne Room.
## Basic game rules
- In the puzzles, the player must push around boulders and avoid obstacles to get to the exit. 
- There are pressure plates and buttons that can be activated by the player, mobs and objects like a boulder, which can unlock other objects in the game.
- Mobs move in predicable ways, or follow the player around.
- If the player is harmed by an object (i.e. being adjacent to the player), the player will take damage. 
- When the player's health points drop to zero, the game reverts to the beginning of the current puzzle. 
- The player can only kill the final boss and must use the environment to his advantage for his defence.
### Default controls
- W, A, S and D for movement
- H for help menu
- O for options menu (for save/load and other options)
- R for restarting the puzzle (when it is impossible to complete)
## Features to implement
This section shall cover the features, catergorized by the **code requirement** items 1 to 5, and others
### Generation of random game sets or events
- Some mobs are spawned outside of the player's vision randomly.
- Some boulders are placed randomly.
- The boss can spawn objects in random positions.
- Exits can be in random positions
### Data structures for storing game status
- a Level Two dimensional array of characters to represent the level, where the origin (0, 0) is topleft of the level.
- a Camera struct that stores the topleft position(x, y) and the camera's width and height.
- a Player struct that stores the health, position, name of the player.
- a MoveableThing struct that stores the health, position and ID of the mobs and obstacles.
- a TurnProcess array that stores the processing order of each object after every player move.
### Dynamic memory management
- Since levels can be in different sizes, Level is loaded dynamically.
- Since the number of mobs can fluctuate in a level, TurnProcess is also loaded dynamically.
### File input/output
- Save and loading a save file.
- Loading levels.
- Loading story.
### Program codes in multiple files
- A object struct header that stores the data structures used
- A misc file that stores miscellaneous functions, i.e. random number generator 
- A level handler file that defines functions to update and manipulate the Level.
- A camera handler file that updates the Camera struct according to player position.
- A draw level file that draws the visible area according to the camera position.
- A player handler file that handles player inputs, and manipulates the Player struct
- An object handler file that handles the object order
- A draw menu file that draws the menu
### Others
- Level editor and simplified level format 