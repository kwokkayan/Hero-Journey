#include <iostream>

#include "baseClasses.h"
#include "moveable.h"
#include "colorIO.h"
#include "objectStack.h"
#include "map.h"
#include "camera.h"
#include "zombie.h"
#include "gameFunctions.h"


int main() {
  std::string levelFile = "level1.txt";
  std::vector<Moveable*> mobQueue;

  Map map = Map();
  map.createEmptyMap(10, 10, 5);

  Player *player = nullptr;
  Camera *camera = nullptr;

  game_func::readLevel(levelFile, map, mobQueue, player, camera);
  game_func::gameLoop(map, mobQueue, player, camera);
}
