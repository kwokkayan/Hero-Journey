// Filename: openable.h
// Description: Header that declares the Openable class.
// Last Changed: 19 Nov, 2020
#include "baseClasses.h"

#ifndef OPENABLE_H
#define OPENABLE_H
  // This class extends Object.
  // isOpened sets the opened state for the Openable
  // activatorObj sets the source of activation
  // functions are commented in openable.cpp
  class Openable : public Object {
    public:
      bool isOpened;
      Object *activatorObj;
      Openable(ObjectId id, ObjectIcon icon, int px, int py);
      Openable(bool io, Object *ao, ObjectId id, ObjectIcon icon, int px, int py);
      virtual void open();
      virtual void close();
  };
#endif
