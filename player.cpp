#include <iostream>

#include "player.h"
#include "colorIO.h"
#include "void.h"

Player::Player(std::string n, int px, int py) : Object(ObjectId::PLAYER, ObjectIcon::PLAYER, px, py) {
  hp = 3;
  name = n;
}
void Player::movement(int dx, int dy) {
  pos.x += dx;
  pos.y += dy;
}
void Player::process(Point p) {
  pos = p;
}
bool Player::check(Point p, Map m) {
  if (!((p.x >= 0 || p.x <= m.getWidth()) && (p.y >= 0 || p.y <= m.getHeight())))
    return false;

  Object *nextObject = m.getObject(p);
  if (nextObject->isValid()) { //if valid spot then gogogo
    std::cout << "validdesu\n";
    nextObject->process(p);
    this->process(p);
    return true;
  } else if (nextObject->id == ObjectId::VOID || nextObject->id == ObjectId::TOPWALL || nextObject->id == ObjectId::SIDEWALL) {
    return false;
  }

  Point nextP = Point(2 * p.x - pos.x, 2 * p.y - pos.y);
  std::cout << "nextP = " << nextP.x << " " << nextP.y << '\n';
  if ((nextP.x >= 0 && nextP.x < m.getWidth()) && (nextP.y >= 0 && nextP.y < m.getHeight())) {
    std::cout << "nextP is valid\n";
    Object *nextnextObject = m.getObject(nextP);

    if (nextObject->check(nextnextObject)) {
      nextObject->process(nextP);
      nextnextObject->process(nextP);
      this->process(p);
      return true;
    }
  }
  return false;
  //return m.getObject(p)->check(nextP, m);
}
void Player::draw() {
  std::cout << addFGColor(FGCode::CYAN) << static_cast<char>(icon) << reset();
}
