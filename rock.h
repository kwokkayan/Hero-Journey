#include "baseClasses.h"

#ifndef ROCK_H
#define ROCK_H
  class Rock : public Object {
    public:
      Rock(int px, int py);
      void moveRock(Point p);
      void process(Point p);
      bool check(Object *o);
      bool isValid();
      void draw();
  };
#endif
