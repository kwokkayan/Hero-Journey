// Filename: map.cpp
// Description: Program that implements the map functions.
// Last Changed: 19 Nov, 2020
#include <iostream>

#include "map.h"
#include "floor.h"
#include "wall.h"
#include "void.h"
#include "zombie.h"
#include "pressurePlate.h"
// Constructors for map
Map::Map() {
  width = 0;
  height = 0;
  mapPtr = nullptr;
}
Map::Map(int w, int h, int d) { //the real empty map
  width = w;
  height = h;
  depth = d;
  mapPtr = new ObjectStack**[height];
  for (int i = 0; i < height; i++) { // The nested loop initialises the ObjectStack array
    mapPtr[i] = new ObjectStack*[width];
    for (int j = 0; j < width; j++) {
      mapPtr[i][j] = new ObjectStack(depth);
    }
  }
}
// This function creates an "empty" map,
// which are walls at the edges surrounding the floors.
// It is essentially a room with four walls.
void Map::createEmptyMap(int w, int h, int d) {
  width = w;
  height = h;
  depth = d;

  mapPtr = new ObjectStack**[height];
  for (int i = 0; i < height; i++) {
    mapPtr[i] = new ObjectStack*[width];
    for (int j = 0; j < width; j++) {
      mapPtr[i][j] = new ObjectStack(depth);
      if ((i > 0 || i < height) && (j == 0 || j == width - 1)) // Checks whether this tile should be a wall or floor
        this->insertObject(new Wall(true, j, i));
      else if (i == 0 || i == height - 1)
        this->insertObject(new Wall(false, j, i));
      else
        this->insertObject(new Floor(j, i));
    }
  }
}
// This function deletes the ObjectStack by releasing the pointers
void Map::deleteMap() {
  for (int i = 0; i < height; i++) { // This loop releases each ObjectStack
    for (int j = 0; j < width; j++) {
      mapPtr[i][j]->deleteStack();
      delete mapPtr[i][j];
    }
    delete[] mapPtr[i];
  }
  delete[] mapPtr;
}
// This function updates part of the map.
// A box is defined and everything in that box is checked and updated if needed
// center is the center of the update box
// w is the width of that box
// In the game loop, Objects' xy are updated after movement, but the map remains the same.
// So this function moves these updated objects to their correct position.
void Map::updateMap(Point center, int w) {
  for (int i = center.y - w; i < center.y + w; i++) {
    // These two ifs checks whether the y-coordinate exceeds the limits of the map
    // and terminate the loop if needed
    if (i < 0)
      continue;
    if (i >= height)
      break;

    for (int j = center.x - w; j < center.x + w; j++) {
      // These two ifs checks whether the x-coordinate exceeds the limits of the map
      // and terminate the loop if needed
      if (j < 0)
        continue;
      if (j >= width)
        break;

      Point currPos = Point(j, i);
      Object *currObj = this->getObject(currPos);

      if (currObj->pos.equalsTo(currPos)) // if same then nothing happens
        continue;

      Object *destObj = this->getObject(currObj->pos);
      if (!destObj->pos.equalsTo(currObj->pos))
        this->moveObject(currObj->pos, destObj->pos);

      this->moveObject(currPos, currObj->pos);
      // Update state for pressurePlate (Someone left the pressurePlate)
      Object *newCurrObj = this->getObject(currPos);
      if (newCurrObj->id == ObjectId::PRESSUREPLATE) {
        PressurePlate *pp = static_cast<PressurePlate*>(newCurrObj);
        pp->deactivate();
      }
    }
  }
}
// These 2 functions pushes the object pointer into the ObjectStack
void Map::insertObject(Object *o) {
  mapPtr[o->pos.y][o->pos.x]->push(o);
}
void Map::insertObject(Object *o, Point p) {
  mapPtr[p.y][p.x]->push(o);
}
// These 2 functions removes the object pointer at the point from the ObjectStack and return it
// if the input coordinates are out of bounds, then return nullptr
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
// These 2 functions returns the Object at the point from the ObjectStack
// if the input coordinates are out of bounds, then return nullptr
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
// This function moves an object from one point to another
// by removing it and inserting it in the new position
void Map::moveObject(Point from, Point to) {
  Object *o = this->removeObject(from);
  if (o != nullptr)
    this->insertObject(o, to);
}
// These two functions returns the total number of objects in the ObjectStack
int Map::numOfObject(Point p) {
  return mapPtr[p.y][p.x]->size();
}
int Map::numOfObject(int px, int py) {
  return mapPtr[py][px]->size();
}
// this returns the width of the map
int Map::getWidth() { return width; }
// this returns the height of the map
int Map::getHeight() { return height; }
// this returns the depth of the map
int Map::getDepth() { return depth; }
