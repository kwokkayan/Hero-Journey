// Filename: player.cpp
// Description: Program that implements the player class.
// Last Changed: 19 Nov, 2020
#include <iostream>

#include "player.h"
#include "colorIO.h"
#include "void.h"
// Constructors for player
Player::Player(std::string n, int px, int py) : Moveable(ObjectId::PLAYER, ObjectIcon::PLAYER, px, py) {
  hp = 100;
  name = n;
  justTookDmg = false;
  justHealed = false;
}
Player::Player(std::string n, int h, bool jtd, bool jh, int px, int py) : Moveable(ObjectId::PLAYER, ObjectIcon::PLAYER, px, py) {
  hp = h;
  name = n;
  justTookDmg = jtd;
  justHealed = jh;
}
// This function reduces the player's hp by 1
void Player::takeDmg() {
  --hp;
  justTookDmg = true;
}
// This function adds the player's hp by health
void Player::heal(int health) {
  hp += health;
  justHealed = true;
}
// This functions sets the player's postion to p
void Player::process(Point p) {
  pos = p;
}
// This function checks whether the player can move into Point p
// p is the destination for the player
// m is the map of the level

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
// This function is executed when a mob interactes with the player
// The player is damaged each time this happens.
bool Player::isValid() { //Take damage
  this->takeDmg();
  return false;
}
// If justTookDmg is true: the icon will be in red
// If justHealed is true: the icon will be in green
// In other casesm the icon will be cyan
void Player::draw() {
  if (justTookDmg) {
    std::cout << addFGColor(FGCode::RED) << static_cast<char>(icon) << reset();
    justTookDmg = false;
  } else if (justHealed) {
    std::cout << addFGColor(FGCode::GREEN) << static_cast<char>(icon) << reset();
    justHealed = false;
  } else {
    std::cout << addFGColor(FGCode::CYAN) << static_cast<char>(icon) << reset();
  }
}
// These three functions prints the player information in-game
void Player::printName() {
  std::cout << "Your name: " << name << '\n' << reset();
}
void Player::printHP() {
  std::cout << "Your HP: " << hp << '\n' << reset();
  if (justTookDmg) {
    std::cout << addFGColor(FGCode::RED) << "You just took damage!" << reset() << '\n';
  } else if (justHealed) {
    std::cout << addFGColor(FGCode::GREEN) << "You just Healed!" << reset() << '\n';
  }
}
void Player::printXY() {
  std::cout << "Your Location(x, y): " << '(' << pos.x << ", " << pos.y << ")\n";
}
