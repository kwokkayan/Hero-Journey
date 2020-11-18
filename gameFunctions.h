//#include "baseClasses.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <time.h>

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
#include "winTile.h"
#include "infoTile.h"

#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H
namespace game_func {
  enum class menuFunctions {
    RESTART,
    SAVE,
    LOAD,
    LEAVEGAME,
    LEAVEMENU
  };
  enum class mainMenuFunctions {
    SELECT,
    LOAD,
    LEAVEGAME
  };
  char getKeystroke();
  void setFormat(int w);
  void detectGameControls(Player *p, Point &pos);
  void clrScr(int t);

  void drawUI(Player* p); //IOMANIP
  void drawMenu(std::string address); //all are in menu dir

  void selectSlotToSave(std::vector<int> options, int &sel);
  void selectSlotToLoad(std::vector<int> options, int &sel);
  void drawSaveMenu(std::vector<int> &existingSavesId);
  void drawLoadMenu(std::vector<int> &existingSavesId);

  void drawMainMenu();
  void handleMainMenu(int levels, Map &map, WinTile *&wintile, std::vector<Moveable*> &mobQueue, Player *&player, Camera *&camera);
  void drawLevelSelectMenu(int levels, std::vector<int> &existingLevelsId);

  void menuLoop(game_func::menuFunctions &f);
  void mainMenuLoop(game_func::mainMenuFunctions &f);

  void printLoseScreen(); //IOMANIP
  void printWinScreen();  //IOMANIP

  void readLevel(std::string levelFile, Map &map, WinTile *&wintile, std::vector<Moveable*> &mobQueue, Player *&p, Camera *&c);
  void gameLoop(Map &map, WinTile *&wintile, std::vector<Moveable*> &mobQueue, Player *&player, Camera *&camera);

  void save(std::string address, Map map, Camera *c);
  void load(std::string address, Map &map, WinTile *&win, std::vector<Moveable*> &mobQueue, Player *&p, Camera *&c);

}
#endif
