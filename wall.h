#include "baseClasses.h"
#include "camera.h"
#include "map.h"

#ifndef WALL_H
#define WALL_H
  class Wall : public Object { //The floor
    public:
      bool isSideWall;
      Wall(bool isw, int px, int py);
      void process(Point p);
      bool check(Object *o);
      bool isValid();
      void draw();
  };
#endif
