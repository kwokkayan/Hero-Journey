#include <vector>
#include "camera.h"
#include "map.h"
#include "moveable.h"

#ifndef LEVELOBJECT_H
#define LEVELOBJECT_H

void levelObject(std::string levelFile, Map &map, std::vector<Moveable*> &mobQueue, Player* p, Camera* c);

#endif
