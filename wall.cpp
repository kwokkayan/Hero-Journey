// Filename: wall.cpp
// Description: Program that implements the Wall class.
// Last Changed: 19 Nov, 2020
#include <iostream>

#include "wall.h"
#include "colorIO.h"
// Constructor for Wall
Wall::Wall(bool isw, int px, int py) : Object(ObjectId::VOID, ObjectIcon::VOID, px, py) {
  isSideWall = isw;
  if (isSideWall) {
    icon = ObjectIcon::SIDEWALL;
    id = ObjectId::SIDEWALL;
  } else {
    icon = ObjectIcon::TOPWALL;
    id = ObjectId::TOPWALL;
  }
}
void Wall::process(Point p) {
  //empty
}
bool Wall::check(Object *o) {
  return false;
}
// Nothing can walk through the wall
bool Wall::isValid() {
  return false;
}
void Wall::draw() {
  std::cout << static_cast<char>(icon) << reset();
}
