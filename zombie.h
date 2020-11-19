// Filename: zombie.h
// Description: Header that declares the Zombie class.
// Last Changed: 19 Nov, 2020
#include "moveable.h"
#include "map.h"

#ifndef ZOMBIE_H
#define ZOMBIE_H
  // Zombie class implements the virtual functions from Objects and Moveable
  // and are documented in zombie.cpp
  // Zombies move in random direction and damages the player when in contact
  // Zombies are crushed by rock and are destroyed 
  class Zombie : public Moveable {
    public:
      Zombie(int px, int py);
      void move(Map m);
      void dealDmg(Moveable *m);

      void process(Point p);
      bool check(Point p, Map m);
      bool isValid();
      void draw();
  };
#endif
