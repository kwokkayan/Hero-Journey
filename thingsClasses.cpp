#include "thingsClasses.h"
Point::Point() {
  x = -1;
  y = -1;
}
Point::Point(int px, int py) {
  x = px;
  y = py;
}
int Point::getX() { return x; }
int Point::getY() { return y; }
void Point::changePos(int px, int py) {
  x = px;
  y = py;
}
int Point::distanceTo(Point p) {
    //TODO: IMPLEMENT THIS FOR PATHFINDING
}

Object::Object() {
  id = 0;
  icon = ' ';
  pos = Point();
}
Object::Object(int px, int py) {
  id = 0;
  icon = ' ';
  pos = Point(px, py);
}
Object::Object(int Id, char Icon, int px, int py){
  id = Id;
  icon = Icon;
  pos = Point(px, py);
}
int Object::getId() { return id; }
char Object::getIcon() { return icon; }

Player::Player() {
  hp = 3;
  name = "Bob";
  //TODO: future implementation
}