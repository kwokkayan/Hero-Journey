// Filename: player.h
// Description: Header that declares the player class.
// Last Changed: 19 Nov, 2020
#include <string>

#include "moveable.h"
#include "map.h"

#ifndef PLAYER_H
#define PLAYER_H
  // Player is derived from Moveable (refer to Moveable.h and Moveable.cpp for documentation)
  // hp is the health of the player.
  // When it is reduced to 0 or below, then the game is over.
  // justTookDmg and justHealed are flags that changes color of text of player information
  // based on the situation
  // name is the name of the player
  // The comments of functions are in player.cpp
  class Player : public Moveable {
    public:
      int hp;
      bool justTookDmg, justHealed;
      std::string name;
      Player(std::string n, int px, int py);
      Player(std::string n, int hp, bool jtd, bool jh, int px, int py); //for save/load
      void takeDmg();
      void heal(int health);

      void process(Point p);
      bool check(Point p, Map m);
      bool isValid();
      void draw();

      void printName();
      void printHP();
      void printXY();
  };
#endif
