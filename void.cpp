// Filename: void.cpp
// Description: Header that implements the Void class.
// Last Changed: 19 Nov, 2020
#include <iostream>

#include "void.h"
#include "colorIO.h"
// Constructors for Void
Void::Void() : Object(ObjectId::VOID, ObjectIcon::VOID, -1, -1) {}
Void::Void(int px, int py) : Object(ObjectId::VOID, ObjectIcon::VOID, px, py) {}
void Void::process(Point p) {

}
bool Void::check(Object *o) {
  return false;
}
// No entities can walk through void
bool Void::isValid() {
  return false;
}
void Void::draw() {
  std::cout << static_cast<char>(icon) << reset();
}
