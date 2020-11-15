//#include "baseClasses.h"
#include "map.h"
#include "camera.h"
#include "player.h"
#include "pressurePlate.h"
#include "rock.h"
#include "door.h"

#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H
namespace game_func {
  char getKeystroke();
  Point detectGameControls(Player *p);
  int processControls(Point pos, Map m, Camera *c, Player *p);
  void movePlayerAndCamera(Map m, Camera *c, Player *p, Point pos);
}
#endif
