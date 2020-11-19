// Filename: void.h
// Description: Header that declares the Void class.
// Last Changed: 19 Nov, 2020
#include "baseClasses.h"
#include "camera.h"
#include "map.h"

#ifndef VOID_H
#define VOID_H
  // Wall extends from Object and implements virtual functions,
  // which are documented in wall.cpp
  class Void : public Object {
    public:
      Void();
      Void(int px, int py);
      void process(Point p);
      bool check(Object *o);
      bool isValid();
      void draw();
  };
#endif
