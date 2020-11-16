#include <iostream>

#include "baseClasses.h"
#include "moveable.h"
#include "colorIO.h"
#include "objectStack.h"
#include "map.h"
#include "camera.h"
#include "zombie.h"
#include "gameFunctions.h"
#include "levelObject.h"


int main() {
  std::string levelFile = "level1.txt";
  std::vector<Moveable*> mobQueue;

  Map map = Map();
  map.createEmptyMap(100, 100, 5);

  Player *player = NULL;
  Camera *camera = NULL;


  levelObject(levelFile, map, mobQueue, player, camera);
  game_func::gameLoop(map, mobQueue, player, camera);

}
