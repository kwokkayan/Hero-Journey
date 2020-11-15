#include "baseClasses.h"
#include "camera.h"
#include "map.h"

#ifndef FLOOR_H
#define FLOOR_H
  class Floor : public Object { //The floor
    public:
      Floor(int px, int py);
      void process(Point p);
      bool check(Object *o);
      bool isValid();
      void draw();
  };
#endif
