#include <iostream>

#include "void.h"
#include "colorIO.h"

Void::Void() : Object(ObjectId::VOID, ObjectIcon::VOID, -1, -1) {}
Void::Void(int px, int py) : Object(ObjectId::VOID, ObjectIcon::VOID, px, py) {}
void Void::process() {
  //empty
}
bool Void::check(Object *o) {
  return false;
}
void Void::draw() {
  std::cout << static_cast<char>(icon) << reset();
}
