#include "baseClasses.h"
#include "objectStack.h"

#ifndef MAP_H
#define MAP_H
  class Map {
      private:
        int width, height;
        ObjectStack ***mapPtr; //make into 3-dimensional, last dimension being a stack
      public:
        Map();
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

        int getWidth();
        int getHeight();
  };
#endif
