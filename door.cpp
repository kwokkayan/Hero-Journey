// Filename: door.cpp
// Description: Program that implements the Door class.
// Last Changed: 19 Nov, 2020
#include <iostream>

#include "door.h"
#include "colorIO.h"
// Constructors for Door
Door::Door(int px, int py) : Openable(ObjectId::DOOR, ObjectIcon::DOOR, px, py) {}
Door::Door(bool io, int px, int py) : Openable(io, nullptr, ObjectId::DOOR, ObjectIcon::DOOR, px, py) {}
Door::Door(bool io, Object *ao, int px, int py) : Openable(io, ao, ObjectId::DOOR, ObjectIcon::DOOR, px, py) {}

void Door::open() {
  isOpened = true;
}
void Door::close() {
  isOpened = false;
}
void Door::process(Point p) {
  //empty
}
// If the door has no pressurePlate, then it can be opened by the player
bool Door::check(Object* o) {
  if (activatorObj == nullptr)
    this->open();
  return false;
}
// If door is closed then cannot move into it
bool Door::isValid() {
  return isOpened;
}
// Door has green background when opened, and red when closed
void Door::draw() {
  if (isOpened)
    std::cout << addBGColor(BGCode::GREEN) << static_cast<char>(icon) << reset();
  else
    std::cout << addFGColor(FGCode::BRIGHT_WHITE) << addBGColor(BGCode::BRIGHT_RED) << static_cast<char>(icon) << reset();
}
