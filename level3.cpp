#include <iostream>
#include <vector>

#include "baseClasses.h"
#include "moveable.h"
#include "colorIO.h"
#include "objectStack.h"
#include "map.h"
#include "camera.h"
#include "zombie.h"
#include "snake.h"
#include "winTile.h"
#include "infoTile.h"
#include "gameFunctions.h"


int main() {
  std::string levelFile = "level3.txt";
  std::vector<Moveable*> mobQueue;

  Map map = Map();
  map.createEmptyMap(15, 15, 5);

  Player *player = nullptr;
  Camera *camera = nullptr;

  game_func::readLevel(levelFile, map, mobQueue, player, camera);
  game_func::gameLoop(map, mobQueue, player, camera);
}
