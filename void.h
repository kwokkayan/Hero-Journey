#include "baseClasses.h"
#include "camera.h"
#include "map.h"

#ifndef VOID_H
#define VOID_H
  class Void : public Object { //The floor
    public:
      Void(int px, int py);
      void process();
      bool check(Object *o);
      void draw();
  };
#endif
