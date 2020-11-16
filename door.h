#include "baseClasses.h"
#include "openable.h"

#ifndef DOOR_H
#define DOOR_H
  class Door : public Openable {
    public:
      Door(int px, int py);

      void open();
      void close();

      void process(Point p);
      bool check(Object *o);
      bool isValid();
      void draw();
  };
#endif
