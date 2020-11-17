#include <string>


#include "moveable.h"
#include "map.h"

#ifndef PLAYER_H
#define PLAYER_H
  class Player : public Moveable { //The player
    public:
      int hp;
      bool justTookDmg;
      std::string name;
      Player(std::string n, int px, int py);
      Player(std::string n, int hp, bool justTookDmg, int px, int py); //for save/load
      void takeDmg();

      void process(Point p);
      bool check(Point p, Map m);
      bool isValid();
      void draw();

      void printName();
      void printHP();
      void printXY();
  };
#endif
