#include <vector>

#include "moveable.h"
#include "map.h"
#include "player.h"

#ifndef SNAKE_H
#define SNAKE_H
  class Snake : public Moveable {
    public:
      std::vector<Point> plist; //closest points to player
      Player *player; //get player pos
      int viewDistance;
      
      Snake(Player *p, int px, int py);
      void move(Map m);
      void dealDmg(Moveable *m);

      void process(Point p);
      bool check(Point p, Map m);
      bool isValid();
      void draw();
  };
#endif
