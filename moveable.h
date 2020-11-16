#include "baseClasses.h"
#include "map.h"

#ifndef MOVEABLES_H
#define MOVEABLES_H
  class Moveable : public Object {
    public:
      Moveable(ObjectId id, ObjectIcon icon, int px, int py);
      virtual void move(Map m);
      virtual void dealDmg(Moveable *mob);
      virtual void takeDmg();
  };
#endif
