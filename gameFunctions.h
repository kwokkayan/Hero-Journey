//#include "baseClasses.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>

#include "baseClasses.h"
#include "colorIO.h"
#include "moveable.h"
#include "objectStack.h"
#include "map.h"
#include "camera.h"
#include "player.h"
#include "door.h"
#include "floor.h"
#include "pressurePlate.h"
#include "zombie.h"
#include "rock.h"
#include "wall.h"

#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H
namespace game_func {
  char getKeystroke();
  Point detectGameControls(Player *p);
  void drawUI(Player* p);
  void printLoseScreen();
  void readLevel(std::string levelFile, Map &map, std::vector<Moveable*> &mobQueue, Player *&p, Camera *&c);
  void gameLoop(Map m, std::vector<Moveable*> mobQueue, Player *player, Camera *camera);
}
#endif
