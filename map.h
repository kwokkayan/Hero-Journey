#include "thingsClasses.h"
#include "objectStack.h"
#ifndef MAP_H
#define MAP_H
  class Map {
      private:
        int width, height;
        ObjectStack **mapPtr; //make into 3-dimensional, last dimension being a stack
      public:
        Map();
        void createEmptyMap(int w, int h, int depth);
        void deleteMap();
        void insertObject(Object o, int px, int py);
        void insertObject(Object o, Point p);
        Object removeObject(int px, int py);
        Object removeObject(Point p);
        Object getObject(int px, int py);
        Object getObject(Point p);
        int getWidth();
        int getHeight();
  };
#endif
