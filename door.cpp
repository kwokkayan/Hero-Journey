#include <iostream>

#include "door.h"
#include "colorIO.h"

Door::Door(int px, int py) : Openable(ObjectId::DOOR, ObjectIcon::DOOR, px, py) {}

void Door::open() {
  isOpened = true;
}
void Door::close() {
  isOpened = false;
}
void Door::process(Point p) {
  //empty
}
bool Door::check(Object* o) {
  if (activatorObj == nullptr) //mobs can open doors :(
    this->open();
  return false;
}
bool Door::isValid() {
  return isOpened;
}
void Door::draw() {
  if (isOpened)
    std::cout << addBGColor(BGCode::GREEN) << static_cast<char>(icon) << reset();
  else
    std::cout << addFGColor(FGCode::BRIGHT_WHITE) << addBGColor(BGCode::BRIGHT_RED) << static_cast<char>(icon) << reset();
}
