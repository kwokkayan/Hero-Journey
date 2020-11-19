// Filename: wall.h
// Description: Header that declares the Wall class.
// Last Changed: 19 Nov, 2020
#include "baseClasses.h"
#include "camera.h"
#include "map.h"

#ifndef WALL_H
#define WALL_H
  class Wall : public Object {
    // Wall extends from Object and implements virtual functions,
    // which are documented in wall.cpp
    // when isSideWall is true, the display icon will be '|' instead of '='
    public:
      bool isSideWall;
      Wall(bool isw, int px, int py);
      void process(Point p);
      bool check(Object *o);
      bool isValid();
      void draw();
  };
#endif
