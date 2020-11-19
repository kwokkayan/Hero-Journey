// Filename: door.h
// Description: Header that declares the Door class.
// Last Changed: 19 Nov, 2020
#include "baseClasses.h"
#include "openable.h"

#ifndef DOOR_H
#define DOOR_H
  // Door implements virtual functions of Openable and Object
  // and are commented in door.cpp
  class Door : public Openable {
    public:
      Door(int px, int py);
      Door(bool io, int px, int py);
      Door(bool io, Object *ao, int px, int py);
      void open();
      void close();

      void process(Point p);
      bool check(Object *o);
      bool isValid();
      void draw();
  };
#endif
