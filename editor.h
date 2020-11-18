#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

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

#ifndef EDITOR_H
#define EDITOR_H
namespace editor {
  void createLevel(std::string levelFile, Map &map, WinTile *&wintile, std::vector<Moveable*> &mobQueue, Player *&player, Camera *&camera);
}
#endif
