#include "thingsClasses.h"
#include "map.h"
#include "camera.h"
#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H
namespace game_func {
  char getKeystroke();
  int detectGameControls(Map &m, Camera &c, Player &p);
  void movePlayerAndCamera(Map &m, Camera &c, Player &p, Point pos);
}
#endif
