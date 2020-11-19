// Filename: infoTile.h
// Description: Header that declares the infoTile class.
// Last Changed: 19 Nov, 2020
#include "baseClasses.h"

#ifndef INFOTILE_H
#define INFOTILE_H
  // InfoTile extends from Object and implements virtual functions,
  // which are documented in infoTile.cpp
  // When the player steps on the tile, some text would be displayed to the player,
  // which is stored in a txt file
  // info stores the text of the information
  // address stores the address of the text file of the information
  class InfoTile : public Object {
    public:
      std::string info, address;
      InfoTile(std::string a, int px, int py);
      void process(Point p);
      bool check(Object *o);
      bool isValid();
      void draw();
  };
#endif
