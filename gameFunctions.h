//#include "baseClasses.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

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
#include "winTile.h"
#include "infoTile.h"
#include "wall.h"
#include "snake.h"
#include "void.h"

#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H
namespace game_func {
  char getKeystroke();
  Point detectGameControls(Player *p);
  void clrScr(int t);
  void drawUI(Player* p); //IOMANIP
  void printLoseScreen(); //IOMANIP
  void printWinScreen();  //IOMANIP
  void readLevel(std::string levelFile, Map &map, std::vector<Moveable*> &mobQueue, Player *&p, Camera *&c);
  void gameLoop(Map m, WinTile *wintile, std::vector<Moveable*> mobQueue, Player *player, Camera *camera);

  void save(std::string address, Map map, Camera *c);
  void load(std::string address, Map &map, WinTile *&win, std::vector<Moveable*> &mobQueue, Player *&p, Camera *&c);
}
#endif
