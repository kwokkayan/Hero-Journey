#include "moveable.h"
#include "map.h"
#ifndef ZOMBIE_H
#define ZOMBIE_H
  class Zombie : public Moveable {
    public:
      Zombie(int px, int py);
      ~Zombie();
      void move(Map m);
      void dealDmg(Moveable *m);

      void process(Point p);
      bool check(Point p, Map m);
      bool isValid();
      void draw();
  };
#endif
