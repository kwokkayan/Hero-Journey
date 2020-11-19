// Filename: main.cpp
// Description: Program that declares game variables and begins the game.
// Last Changed: 19 Nov, 2020
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "moveable.h"
#include "player.h"
#include "map.h"
#include "camera.h"
#include "gameFunctions.h"
#include "editor.h"
// In main, game variables map, player, camera, wintile, and mobQueue are declared
//  -map stores the level of the game.
//  -player stores player information (position, health, name).
//  -camera stores camera information (position, length of camera).
//  -wintile stores the level position of the level finish.
//  -mobQueue stores pointers of all mobs for processing.
// After declaration, the main menu of the game is displayed.
// When a level and difficulty is selected, the variables are initialised.
// Then the game begins.
int main() {
  //set seed for rand()
  srand(time(NULL));

  // game variables
  Map map = Map();
  Player *player = nullptr;
  Camera *camera = nullptr;
  WinTile *wintile = nullptr;
  std::vector<Moveable*> mobQueue;
  // selection flags.
  // isStoryMode is true when story mode is selected, false otherwise.
  // returnMainMenu is true when player decides to return to main menu from the game, false otherwise.
  bool isStoryMode, returnMainMenu;
  //editor::createLevel("level6/level6.txt", map, wintile, mobQueue, player, camera);

  // Each iteration, player is set to nullptr, all flags set to false, as handleMainMenu will alter them.
  // handleMainMenu prints the main menu and process the inputs
  // Game starts when a level is selected and loaded (i.e. player is initialised)
  do {
    player = nullptr;
    isStoryMode = false;
    returnMainMenu = false; //for second loop
    game_func::handleMainMenu(5, map, wintile, mobQueue, player, camera, isStoryMode);
    if (player != nullptr) {
      game_func::gameLoop(map, wintile, mobQueue, player, camera, isStoryMode, returnMainMenu);
      game_func::clearObjects(map, mobQueue, camera); // cautionary clearing
    }
  } while (returnMainMenu);
}
