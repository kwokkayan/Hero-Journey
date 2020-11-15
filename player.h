#include <string>

#include "baseClasses.h"
#include "map.h"

#ifndef PLAYER_H
#define PLAYER_H
  class Player : public Object { //The player
    public:
      int hp;
      std::string name;
      Player(std::string n, int px, int py);
      void movement(int dx, int dy);
      void process(Point p);
      bool check(Point p, Map m);
      void draw();
  };
#endif
