// Filename: thingsClasses.cpp
// Description: Program that tests the classes and functions
// Last Changed: 5 Nov, 2020
#include <iostream>

#include "baseClasses.h"
#include "colorIO.h"
#include "gameFunctions.h"
Point::Point() {
  x = -1;
  y = -1;
}
Point::Point(int px, int py) {
  x = px;
  y = py;
}
void Point::changePos(int px, int py) {
  x = px;
  y = py;
}
int Point::distanceTo(Point p) {
    //TODO: IMPLEMENT THIS FOR PATHFINDING
}
bool Point::equalsTo(Point p) {
  return (x == p.x && y == p.y);
}
bool Point::equalsTo(int px, int py) {
  return (x == px && y == py);
}

Object::Object() {
  id = ObjectId::VOID;
  icon = ObjectIcon::VOID;
  pos = Point();
}
Object::Object(int px, int py) {
  id = ObjectId::VOID;
  icon = ObjectIcon::VOID;
  pos = Point(px, py);
}
Object::Object(ObjectId Id, ObjectIcon Icon, int px, int py){
  id = Id;
  icon = Icon;
  pos = Point(px, py);
}
void Object::process(Point p) {
  //if (id = ObjectId::FLOOR)
}
bool Object::check(Object *o) {
  return false;
}
bool Object::isValid() {
  return false;
}
void Object::draw() {
  std::cout << static_cast<char>(icon) << reset();
}
