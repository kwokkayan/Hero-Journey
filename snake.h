// Filename: snake.h
// Description: Header that declares the Snake class.
// Last Changed: 19 Nov, 2020
#include <vector>

#include "moveable.h"
#include "map.h"
#include "player.h"

#ifndef SNAKE_H
#define SNAKE_H
  // Snake class implements the virtual functions from Object and Moveable
  // and are documented in snake.cpp
  // plist stores the closest points to the player
  // player stores player information, so to access its position.
  // viewDistance is the distance in which the snake will follow the player.
  // Snakes follow the player in range of the viewDistance
  // and stay in place when the player is not in sight
  class Snake : public Moveable {
    public:
      std::vector<Point> plist; //closest points to player
      Player *player; //get player pos
      int viewDistance;

      Snake(Player *p, int px, int py);
      Snake(Player *p, int vd, int px, int py); // For save/load
      Snake(int vd, int px, int py);
      void move(Map m);
      void dealDmg(Moveable *m);

      void process(Point p);
      bool check(Point p, Map m);
      bool isValid();
      void draw();
  };
#endif
