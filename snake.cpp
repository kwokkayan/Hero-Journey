#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "snake.h"
#include "colorIO.h"

Snake::Snake(Player *p, int px, int py) : Moveable(ObjectId::SNAKE, ObjectIcon::SNAKE, px, py) {
  srand(time(NULL)); //it is like this?
  player = p;
  viewDistance = 5;
}
void Snake::move(Map m) {
  std::vector<Point> plist = pos.closestPointsTo(player->pos, viewDistance);
  if (plist.size() > 0) {
    int randIndex = rand() % plist.size();
    if (this->check(plist[randIndex], m))
      pos = plist[randIndex];
  } else {
    //maybe random movement?
  }
}
void Snake::dealDmg(Moveable *p) {
  if (pos.distanceTo(p->pos) == 1)
    p->takeDmg();
}
void Snake::process(Point p) {
  //Kill zom
  destroyFlag = true;
}
bool Snake::check(Point p, Map m) {
  if (!((p.x >= 0 || p.x <= m.getWidth()) && (p.y >= 0 || p.y <= m.getHeight())))
    return false;

  Object *nextObject = m.getObject(p);
  if (nextObject->isValid()) { //if valid spot then gogogo
    nextObject->process(p);
    return true;
  }
  //Can Snakes push rocks?
  return false;
}
bool Snake::isValid() {
  return false;
}
void Snake::draw() {
  std::cout << addFGColor(FGCode::GREEN) << static_cast<char>(icon) << reset();
}