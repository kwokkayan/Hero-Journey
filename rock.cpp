// Filename: rock.cpp
// Description: Program that implements the Rock class.
// Last Changed: 19 Nov, 2020
#include <iostream>

#include "rock.h"
#include "colorIO.h"
// Constructor for Rock
Rock::Rock(int px, int py) : Object(ObjectId::ROCK, ObjectIcon::ROCK, px, py) {}
// When rock is pushed, this function will be called to update position to p
void Rock::process(Point p) {
  pos = p;
}
// This function checks if the rock can be pushed onto the tile
bool Rock::check(Object *o) {
  if (o->id == ObjectId::WINTILE || o->id == ObjectId::INFOTILE)
    return false;
  if (o->id == ObjectId::ZOMBIE || o->id == ObjectId::SNAKE)
    return true;
  return o->isValid();
}
// Rocks can never be stepped on
bool Rock::isValid() {
  return false;
}
// Rocks have no special drawing method
void Rock::draw() {
  std::cout << static_cast<char>(icon) << reset();
}
