// Filename: rock.h
// Description: Header that declares the Rock class.
// Last Changed: 19 Nov, 2020
#include "baseClasses.h"

#ifndef ROCK_H
#define ROCK_H
  // Rock implements the virtual functions of Object
  // and are documented in rock.cpp
  class Rock : public Object {
    public:
      Rock(int px, int py);
      void process(Point p);
      bool check(Object *o);
      bool isValid();
      void draw();
  };
#endif
