// Filename: map.h
// Description: Header that declares the map class
// Last Changed: 19 Nov, 2020
#include "baseClasses.h"
#include "objectStack.h"

#ifndef MAP_H
#define MAP_H
  // The map class stores a level of the game.
  // Each level has a width and height.
  // Depth is defined as the maximum number of Objects at a given spot.
  // The detailed implementation of each tile of the map can be found in ObjectStack.cpp and ObjectStack.h
  // Comments for functions will be in map.cpp
  class Map {
      private:
        int width, height, depth;
        ObjectStack ***mapPtr;
      public:
        Map();
        Map(int w, int h, int d);
        void createEmptyMap(int w, int h, int depth);
        void deleteMap();
        void updateMap(Point center, int w);

        void insertObject(Object *o);
        void insertObject(Object *o, Point p);

        Object* removeObject(int px, int py);
        Object* removeObject(Point p);

        Object* getObject(int px, int py);
        Object* getObject(Point p);

        void moveObject(Point from, Point to);

        int numOfObject(Point p);
        int numOfObject(int px, int py);

        int getWidth();
        int getHeight();
        int getDepth();
  };
#endif
