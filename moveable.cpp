#include "moveable.h"

Moveable::Moveable(ObjectId id, ObjectIcon icon, int px, int py) : Object (id, icon, px, py) {}

void Moveable::move(Map m) {}
void Moveable::dealDmg(Moveable *mob) {}
void Moveable::takeDmg() {}
