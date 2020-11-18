#include <iostream>

#include "moveable.h"
#include "player.h"
#include "map.h"
#include "camera.h"
#include "gameFunctions.h"
#include "editor.h"

int main(int argc, char* argv[]) {
  //std::string levelFileAddress;
  //std::cout << "input level file path: ";
  //std::cin >> levelFileAddress;
  std::string flag = argv[1];

  Map map = Map();
  Player *player = nullptr;
  Camera *camera = nullptr;
  WinTile *wintile = nullptr;
  std::vector<Moveable*> mobQueue;

  if (flag == "editor") {
    editor::createLevel("level6/level6.txt", map, wintile, mobQueue, player, camera);
  } else {
    game_func::readLevel("level5/level5.txt", map, wintile, mobQueue, player, camera);
  }
  game_func::gameLoop(map, wintile, mobQueue, player, camera);
}
