#include "baseClasses.h"

#ifndef INFOTILE_H
#define INFOTILE_H
  class InfoTile : public Object { //preload
    public:
      std::string info, address;
      InfoTile(std::string a, int px, int py);
      void process(Point p);
      bool check(Object *o);
      bool isValid();
      void draw();
  };
#endif
