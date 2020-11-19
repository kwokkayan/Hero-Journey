// Filename: winTile.h
// Description: Header that declares the winTile class.
// Last Changed: 19 Nov, 2020
#include "baseClasses.h"

#ifndef WINTILE_H
#define WINTILE_H
  // winTile extends from Object and implements virtual functions,
  // which are documented in wintile.cpp
  // hasWon is the winning condition and is set when the player stands on the winTile.
  class WinTile : public Object {
    public:
      bool hasWon;
      WinTile(int px, int py);
      WinTile(bool hw, int px, int py);
      void process(Point p);
      bool check(Object *o);
      bool isValid();
      void draw();
  };
#endif
