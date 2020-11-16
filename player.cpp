#include <iostream>

#include "player.h"
#include "colorIO.h"
#include "void.h"

Player::Player(std::string n, int px, int py) : Moveable(ObjectId::PLAYER, ObjectIcon::PLAYER, px, py) {
  hp = 100;
  name = n;
  justTookDmg = false;
}
void Player::takeDmg() {
  --hp;
  justTookDmg = true;
}
void Player::process(Point p) {
  pos = p;
}
bool Player::check(Point p, Map m) {
  if (!((p.x >= 0 || p.x <= m.getWidth()) && (p.y >= 0 || p.y <= m.getHeight())))
    return false;

  Object *nextObject = m.getObject(p);
  if (nextObject->isValid()) { //if valid spot then gogogo
    nextObject->process(p);
    this->process(p);
    return true;
  } else if (nextObject->id == ObjectId::VOID || nextObject->id == ObjectId::TOPWALL || nextObject->id == ObjectId::SIDEWALL) {
    return false;
  }
  //Unopened door
  if (nextObject->id == ObjectId::ROCK) {
    Point nextP = Point(2 * p.x - pos.x, 2 * p.y - pos.y);
    if ((nextP.x >= 0 && nextP.x < m.getWidth()) && (nextP.y >= 0 && nextP.y < m.getHeight())) {
      Object *nextnextObject = m.getObject(nextP);

      if (nextObject->check(nextnextObject)) {
        nextObject->process(nextP);
        nextnextObject->process(nextP);
        this->process(p);
        return true;
      }
    }
  } else nextObject->check(nullptr);
  return false;
  //return m.getObject(p)->check(nextP, m);
}
bool Player::isValid() { //Take damage
  this->takeDmg();
  return false;
}
void Player::draw() {
  if (justTookDmg) {
    std::cout << addFGColor(FGCode::RED) << static_cast<char>(icon) << reset();
    justTookDmg = false;
  } else {
    std::cout << addFGColor(FGCode::CYAN) << static_cast<char>(icon) << reset();
  }
}
void Player::printName() {
  std::cout << "Your name: " << name << '\n' << reset();
}
void Player::printHP() {
  std::cout << "Your HP: " << hp << '\n' << reset();
  if (justTookDmg) {
    std::cout << addFGColor(FGCode::RED) << "You just took damage!" << reset() << '\n';
  }
}
void Player::printXY() {
  std::cout << "Your Location(x, y): " << '(' << pos.x << ", " << pos.y << ")\n";
}
