#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "moveable.h"
#include "player.h"
#include "map.h"
#include "camera.h"
#include "gameFunctions.h"
#include "editor.h"

int main(int argc, char* argv[]) {
  //std::string levelFileAddress;
  //std::cout << "input level file path: ";
  //std::cin >> levelFileAddres
  srand(time(NULL));

  Map map = Map();
  Player *player = nullptr;
  Camera *camera = nullptr;
  WinTile *wintile = nullptr;
  std::vector<Moveable*> mobQueue;
  bool isStoryMode, returnMainMenu;
  //editor::createLevel("level6/level6.txt", map, wintile, mobQueue, player, camera);
  //game_func::readScriptLevel("level5/level5.txt", map, wintile, mobQueue, player, camera);
  do {
    player = nullptr;
    isStoryMode = false;
    returnMainMenu = false; //for second loop
    game_func::handleMainMenu(6, map, wintile, mobQueue, player, camera, isStoryMode); //CHANGE LEVEL NUM
    std::cout << isStoryMode;
    if (isStoryMode) {
      game_func::readScriptLevel("level1/level1m.txt", map, wintile, mobQueue, player, camera);
    }
    if (player != nullptr)
      game_func::gameLoop(map, wintile, mobQueue, player, camera, isStoryMode, returnMainMenu);
  } while (returnMainMenu);
}
