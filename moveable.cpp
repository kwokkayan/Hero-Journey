#include <iostream>

#include "moveable.h"

Moveable::Moveable(ObjectId id, ObjectIcon icon, int px, int py) : Object (id, icon, px, py) {
  destroyFlag = false;
}
Moveable::~Moveable() {
  std::cout << "Moveable is dead\n";
}
void Moveable::move(Map m) {}
void Moveable::dealDmg(Moveable *mob) {}
void Moveable::takeDmg() {}
