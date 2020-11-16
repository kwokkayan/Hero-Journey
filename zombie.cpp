#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "zombie.h"
#include "colorIO.h"

Zombie::Zombie(int px, int py) : Moveable(ObjectId::ZOMBIE, ObjectIcon::ZOMBIE, px, py) {
  srand(time(NULL)); //it is like this?
}
Zombie::~Zombie() {
  std::cout << "Zombie is killed\n";
}
void Zombie::move(Map m) {
  int result = rand() % 5;
  int dx = 0, dy = 0;

  switch (result) {
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

  //std::cout << "zombie: " << dx << " " << dy << "\n";
  Point p = Point(pos.x + dx, pos.y + dy);

  if (!p.equalsTo(pos))
    if (this->check(p, m))
      this->process(p);
}
void Zombie::dealDmg(Moveable *p) {
  if (pos.distanceTo(p->pos) == 1)
    p->takeDmg();
}
void Zombie::process(Point p) {
  pos = p;
}
bool Zombie::check(Point p, Map m) {
  if (!((p.x >= 0 || p.x <= m.getWidth()) && (p.y >= 0 || p.y <= m.getHeight())))
    return false;

  Object *nextObject = m.getObject(p);
  if (nextObject->isValid()) { //if valid spot then gogogo
    nextObject->process(p);
    return true;
  }
  //Can zombies push rocks?
  return false;
}
bool Zombie::isValid() {
  return false;
}
void Zombie::draw() {
  std::cout << addFGColor(FGCode::GREEN) << static_cast<char>(icon) << reset();
}
