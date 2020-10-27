#include "thingsClasses.h"
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

Player::Player(std::string n, int px, int py) : Object(ObjectId::PLAYER, ObjectIcon::PLAYER, px, py){
  hp = 3;
  name = n;
}
void Player::movement(int dx, int dy) {
  pos.x += dx;
  pos.y += dy;
}

Rock::Rock(int px, int py) : Object(ObjectId::ROCK, ObjectIcon::ROCK, px, py) {}

void Rock::moveRock(Point p) {
  //request to map object to change pos. p is for detected where the force came from
}