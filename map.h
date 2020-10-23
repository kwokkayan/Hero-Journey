#include "thingsClasses.h"
#ifndef MAP_H
#define MAP_H
  class Map {
      private:
        int width, height;
        Object **mapPtr;
      public:
        Map();
        void deleteMap();
        void createEmptyMap(int w, int h);
        void insertObject(Object o, int w, int h);
        Object getObject(int w, int h);
  };
#endif