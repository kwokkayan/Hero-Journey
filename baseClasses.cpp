// Filename: baseClasses.cpp
// Description: Program that implements the base classes for objects in game
// Last Changed: 19 Nov, 2020
#include <iostream>
#include <cmath>
#include <limits>

#include "baseClasses.h"
#include "colorIO.h"
#include "gameFunctions.h"
// Object constructors to set class variables
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
// This calculates the distance to another point.
// defined by the formula.
int Point::distanceTo(Point p) {
  return abs(p.x - x) + abs(p.y - y);
}
// This finds the closest adjacent points of this Point to p, inside the range of vd.
// Mainly used for the Snake object, to find the closest Points to the player.
std::vector<Point> Point::closestPointsTo(Point p, int vd) {
  std::vector<Point> plist;

  plist.push_back(Point(x - 1, y));
  plist.push_back(Point(x + 1, y));
  plist.push_back(Point(x, y - 1));
  plist.push_back(Point(x, y + 1));

  int closestDistance = std::numeric_limits<int>::max();
  // Loop that finds the closest distance of the adjacent points to p
  for (std::vector<Point>::iterator it = plist.begin(); it != plist.end(); it++) {
    if (closestDistance > it->distanceTo(p)) {
      closestDistance = it->distanceTo(p);
    }
  }
  std::vector<Point> closest;
  if (closestDistance > vd)
    return closest;

  // Loop that finds the closest points to p
  for (std::vector<Point>::iterator it = plist.begin(); it != plist.end(); it++) {
    if (it->distanceTo(p) <= closestDistance)
      closest.push_back(*it);
  }
  return closest;
}
// These two functions return true when the two points are identical
bool Point::equalsTo(Point p) {
  return (x == p.x && y == p.y);
}
bool Point::equalsTo(int px, int py) {
  return (x == px && y == py);
}
// Object constructors to set class variables
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
// These won't be used in practice, since all real objects in the game have seperate classes
// This function is updates the object state after other objects have interacted with it
void Object::process(Point p) {
}
// This function checks whether o can be interacted or moved onto
bool Object::check(Object *o) {
  return false;
}
// This function returns true or false. If true, other objects can interact with it and move onto it, and false otherwise.
bool Object::isValid() {
  return false;
}
// This function draws the character presentation of the object
void Object::draw() {
  std::cout << static_cast<char>(icon) << reset();
}
