// Filename: moveable.cpp
// Description: Program that implements the moveable class.
// Last Changed: 19 Nov, 2020
#include <iostream>

#include "moveable.h"
// Constructor for Moveable
Moveable::Moveable(ObjectId id, ObjectIcon icon, int px, int py) : Object (id, icon, px, py) {
  destroyFlag = false;
}
// This function is used by Snake and Zombie when they move in the game loop
void Moveable::move(Map m) {}
// This function is used by Snake and Zombie when dealing damage to Player
void Moveable::dealDmg(Moveable *mob) {}
// This function is used by Player when taking damage from Snake and/or Zombie
void Moveable::takeDmg() {}
