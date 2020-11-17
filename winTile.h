#include "baseClasses.h"

#ifndef WINTILE_H
#define WINTILE_H
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
