#include "thingsClasses.h"
#ifndef MAP_H
#define MAP_H
  class Map {
      private:
        int width, height;
        Object **mapPtr; //make into 3-dimensional, last dimension being a stack
      public:
        Map();
        void createEmptyMap(int w, int h);
        void deleteMap();
        void insertObject(Object o, int px, int py);
        void insertObject(Object o, Point p);
        Object getObject(int px, int py);
        Object getObject(Point p);
        int getWidth();
        int getHeight();
  };
#endif