#include <iostream>

#include "rock.h"
#include "colorIO.h"
Rock::Rock(int px, int py) : Object(ObjectId::ROCK, ObjectIcon::ROCK, px, py) {}
void Rock::moveRock(Point p) {
  //request to map object to change pos. p is for detected where the force came from
}
void Rock::process(Point p) {
  //std::cout << "Rock pos change\n";
  pos = p;
}
bool Rock::check(Object *o) {
  //std::cout << "Rock check\n";
  return o->isValid();
}
bool Rock::isValid() {
  //std::cout << "Rock is touched\n";
  return false;
}
void Rock::draw() {
  std::cout << static_cast<char>(icon) << reset();
}
