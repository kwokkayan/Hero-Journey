// Filename: snake.cpp
// Description: Program that implements the Snake class.
// Last Changed: 19 Nov, 2020
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "snake.h"
#include "colorIO.h"
// Constructors for snake class
Snake::Snake(Player *p, int px, int py) : Moveable(ObjectId::SNAKE, ObjectIcon::SNAKE, px, py) {
  player = p;
  viewDistance = 5;
}
Snake::Snake(Player *p, int vd, int px, int py) : Moveable(ObjectId::SNAKE, ObjectIcon::SNAKE, px, py) {
  player = p;
  viewDistance = vd;
}
Snake::Snake(int vd, int px, int py) : Moveable(ObjectId::SNAKE, ObjectIcon::SNAKE, px, py) {
  player = nullptr;
  viewDistance = vd;
}
// This function finds the closest adjacent points of the snake to the player,
// then randomises the points to pick one.
// If that point is valid, then the snake will move there.
void Snake::move(Map m) {
  std::vector<Point> plist = pos.closestPointsTo(player->pos, viewDistance); // Gets the points
  if (plist.size() > 0) {
    int randIndex = rand() % plist.size(); // Randomises the index
    if (this->check(plist[randIndex], m))
      pos = plist[randIndex]; 
  }
}
// This function checks if the player is next to the snake.
// If so, the player will take damage
void Snake::dealDmg(Moveable *p) {
  if (pos.distanceTo(p->pos) == 1)
    p->takeDmg();
}
// This function sets destroyFlag to true when a rock crushes it
void Snake::process(Point p) {
  destroyFlag = true;
}
// This function checks whether the snake can move to the tile at point p.
// If it is valid, then that tile is processed
bool Snake::check(Point p, Map m) {
  if (!((p.x >= 0 || p.x <= m.getWidth()) && (p.y >= 0 || p.y <= m.getHeight())))
    return false;

  Object *nextObject = m.getObject(p);
  if (nextObject->isValid() && nextObject->id != ObjectId::WINTILE && nextObject->id != ObjectId::INFOTILE) { //if valid spot then gogogo
    nextObject->process(p);
    return true;
  }
  return false;
}
// Snakes cannot be stepped on by the player or other mobs
bool Snake::isValid() {
  return false;
}
// Zombies are drawn green
void Snake::draw() {
  std::cout << addFGColor(FGCode::GREEN) << static_cast<char>(icon) << reset();
}
