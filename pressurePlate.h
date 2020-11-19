// Filename: pressurePlate.h
// Description: Header that declares the PressurePlate class.
// Last Changed: 19 Nov, 2020
#include "baseClasses.h"
#include "openable.h"

#ifndef PRESSUREPLATE_H
#define PRESSUREPLATE_H
  // PressurePlate is used for toggling objects with open and close states.
  // isPressed is true when another object is on top of it.
  // activateObj stores the pointer of the objects with open and close states.
  // PressurePlate implements the virtual functions of Object
  // and are documented in rock.cpp, along with other functions
  class PressurePlate : public Object {
    public:
      bool isPressed;
      Openable *activateObj;

      PressurePlate(int px, int py);
      PressurePlate(bool ip, int px, int py);
      PressurePlate(bool ip, Openable *ao, int px, int py);

      void activate();
      void deactivate();
      void process(Point p);
      bool check(Object *o);
      bool isValid();
      void draw();
  };
#endif
