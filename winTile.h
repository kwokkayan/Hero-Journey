#include "baseClasses.h"

#ifndef WINTILE_H
#define WINTILE_H
  class WinTile : public Object {
    public:
      WinTile(int px, int py);
      WinTile(bool hw, int px, int py);
      bool hasWon;
      void process(Point p);
      bool check(Object *o);
      bool isValid();
      void draw();
  };
#endif
