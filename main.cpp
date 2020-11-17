#include <iostream>

#include "moveable.h"
#include "player.h"
#include "map.h"
#include "camera.h"
#include "gameFunctions.h"

int main() {
  //std::string levelFileAddress;
  //std::cout << "input level file path: ";
  //std::cin >> levelFileAddress;

  Map map = Map();
  Player *player = nullptr;
  Camera *camera = nullptr;
  WinTile *wintile = nullptr;
  std::vector<Moveable*> mobQueue;

  game_func::readLevel("level5/level5.txt", map, wintile, mobQueue, player, camera);
  game_func::gameLoop(map, wintile, mobQueue, player, camera);
}
