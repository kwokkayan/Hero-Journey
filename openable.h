#include "baseClasses.h"

#ifndef OPENABLE_H
#define OPENABLE_H
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
