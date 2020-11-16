#include <iostream>

#include "map.h"
#include "floor.h"
#include "wall.h"
#include "void.h"
#include "zombie.h"
#include "pressurePlate.h"

Map::Map() {
  width = 0;
  height = 0;
  mapPtr = nullptr;
}
void Map::createEmptyMap(int w, int h, int depth) {
  width = w;
  height = h;
  mapPtr = new ObjectStack**[height];
  for (int i = 0; i < height; i++) {
    mapPtr[i] = new ObjectStack*[width];
    for (int j = 0; j < width; j++) {
      mapPtr[i][j] = new ObjectStack(depth);
      if ((i > 0 || i < height) && (j == 0 || j == width - 1))
        this->insertObject(new Wall(true, j, i));
      else if (i == 0 || i == height - 1)
        this->insertObject(new Wall(false, j, i));
      else
        this->insertObject(new Floor(j, i));
    }
  }
}
void Map::deleteMap() {
  for (int i = 0; i < height; i++) {
    delete[] mapPtr[i];
  }
  delete[] mapPtr;
}
void Map::updateMap(Point center, int w) {
  for (int i = center.y - w; i < center.y + w; i++) {
    if (i < 0)
      continue;
    if (i > height)
      break;

    for (int j = center.x - w; j < center.x + w; j++) {
      if (j < 0)
        continue;
      if (j > width)
        break;

      Point currPos = Point(j, i);
      Object *currObj = this->getObject(currPos); //so inefficient :(

      if (currObj->pos.equalsTo(currPos)) // if same then nothing happens
        continue;

      Object *destObj = this->getObject(currObj->pos);
      if (!destObj->pos.equalsTo(currObj->pos))
        this->moveObject(currObj->pos, destObj->pos);

      this->moveObject(currPos, currObj->pos);
      //UPDATE STATE FOR PRESSUREPLATE (Someone left the pressurePlate)
      Object *newCurrObj = this->getObject(currPos);
      if (newCurrObj->id == ObjectId::PRESSUREPLATE) { //SO UGLY AR PUKE EMOJI
        PressurePlate *pp = static_cast<PressurePlate*>(newCurrObj);
        pp->deactivate();
      }

    }
  }
}
// A bit stupid - maybe just integrate the stack
void Map::insertObject(Object *o) {
  mapPtr[o->pos.y][o->pos.x]->push(o); //TODO: ERROR HANDLING
}
void Map::insertObject(Object *o, Point p) {
  mapPtr[p.y][p.x]->push(o); //TODO: ERROR HANDLING
}
Object* Map::removeObject(int px, int py) {
  if ((px < 0 || px > this->getWidth()) && (py < 0 || py > this->getWidth()))
    return nullptr;
  return mapPtr[py][px]->pop();
}
Object* Map::removeObject(Point p) {
  if ((p.x < 0 || p.x > this->getWidth()) && (p.y < 0 || p.y > this->getWidth()))
    return nullptr;
  return mapPtr[p.y][p.x]->pop();
}
Object* Map::getObject(int px, int py) {
  if ((px < 0 || px > this->getWidth()) && (py < 0 || py > this->getWidth()))
    return nullptr;
  return mapPtr[py][px]->top();
}
Object* Map::getObject(Point p) {
  if ((p.x < 0 || p.x > this->getWidth()) && (p.y < 0 || p.y > this->getWidth()))
    return nullptr;
  return mapPtr[p.y][p.x]->top();
}
void Map::moveObject(Point from, Point to) {
  Object *o = this->removeObject(from);
  if (o != nullptr)
    this->insertObject(o, to);
}
int Map::getWidth() { return width; }
int Map::getHeight() { return height; }
