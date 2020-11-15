#include "baseClasses.h"
#include "openable.h"

#ifndef PRESSUREPLATE_H
#define PRESSUREPLATE_H
  class PressurePlate : public Object {
    public:
      bool isPressed;
      Openable *activateObj; //multiple stuff array
      PressurePlate(int px, int py);
      void activate();
      void deactivate();
      void process(Point p);
      bool check(Object *o);
      bool isValid();
      void draw();
  };
#endif
