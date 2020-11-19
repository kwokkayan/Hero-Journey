// Filename: moveable.h
// Description: Header that declares the moveable class.
// Last Changed: 19 Nov, 2020
#include "baseClasses.h"
#include "map.h"

#ifndef MOVEABLES_H
#define MOVEABLES_H
  // Moveable extends Object and is the base class for Player, Zombie and Snake.
  // destroyFlag is used for Zombie and Snake, so that they will be removed when neccessary (i.e. getting crushed by rock)
  // Comments for functions are in moveable.cpp
  class Moveable : public Object {
    public:
      bool destroyFlag;
      Moveable(ObjectId id, ObjectIcon icon, int px, int py);
      virtual void move(Map m);
      virtual void dealDmg(Moveable *mob);
      virtual void takeDmg();
  };
#endif
