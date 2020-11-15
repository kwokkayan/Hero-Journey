#include <iostream>

#include "floor.h"
#include "colorIO.h"

Floor::Floor(int px, int py) : Object(ObjectId::FLOOR, ObjectIcon::FLOOR, px, py) {}
void Floor::process(Point p) {
  //empty
}
bool Floor::check(Object *o) {
  return true;
}
bool Floor::isValid() {
  return true;
}
void Floor::draw() {
  std::cout << static_cast<char>(icon) << reset();
}
