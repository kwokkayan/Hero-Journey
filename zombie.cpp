// Filename: zombie.cpp
// Description: Program that implements the Zombie class.
// Last Changed: 19 Nov, 2020
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "zombie.h"
#include "colorIO.h"
// Constructor for Zombie
Zombie::Zombie(int px, int py) : Moveable(ObjectId::ZOMBIE, ObjectIcon::ZOMBIE, px, py) {}
// This functions moves the zombie in a random direction; that is, the 4 adjacent tiles of the zombie
// It can also sometimes stay in the current tiles. The chances are equal.
// If the zombie "decides" to move but the tile is not valid, it will remain in place.
void Zombie::move(Map m) {
  int result = rand() % 5; // random integer from 0 to 4
  int dx = 0, dy = 0;

  switch (result) { // The four possible adjacent tiles
    case 1: {
      ++dx;
      break;
    }
    case 2: {
      --dx;
      break;
    }
    case 3: {
      ++dy;
      break;
    }
    case 4: {
      --dy;
      break;
    }
  }

  Point p = Point(pos.x + dx, pos.y + dy);

  // If p is one of the four possible tiles and it is a valid position, them move to that position.
  if (!p.equalsTo(pos))
    if (this->check(p, m))
      pos = p;
}
// This function checks if the player is next to the zombie.
// If so, the player will take damage
void Zombie::dealDmg(Moveable *p) {
  if (pos.distanceTo(p->pos) == 1)
    p->takeDmg();
}
// This function sets destroyFlag to true when a rock crushes it
void Zombie::process(Point p) {
  destroyFlag = true;
}
// This function checks whether the zombie can move to the tile at point p.
// If it is valid, then that tile is processed
bool Zombie::check(Point p, Map m) {
  if (!((p.x >= 0 || p.x <= m.getWidth()) && (p.y >= 0 || p.y <= m.getHeight())))
    return false;

  Object *nextObject = m.getObject(p);
  if (nextObject->isValid() && nextObject->id != ObjectId::WINTILE && nextObject->id != ObjectId::INFOTILE) { // wintile and infotile can only be accessed by the player
    nextObject->process(p);
    return true;
  }
  return false;
}
// Zombies cannot be stepped on by the player or other mobs
bool Zombie::isValid() {
  return false;
}
// Zombies are drawn green
void Zombie::draw() {
  std::cout << addFGColor(FGCode::GREEN) << static_cast<char>(icon) << reset();
}
