//#include "baseClasses.h"
#include <vector>

#include "map.h"
#include "camera.h"
#include "player.h"
#include "pressurePlate.h"
#include "rock.h"
#include "door.h"
#include "moveable.h"

#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H
namespace game_func {
  char getKeystroke();
  Point detectGameControls(Player *p);
  void drawUI(Player* p);
  void gameLoop(Map m, std::vector<Moveable*> mobQueue, Player *player, Camera *camera);
}
#endif
