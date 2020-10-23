#include "map.h"
Map::Map() {
  width = 0;
  height = 0;
  mapPtr = nullptr;
}
void Map::createEmptyMap(int w, int h) {
  width = w;
  height = h;
  mapPtr = new Object*[h];
  for (int i = 0; i < height; i++) {
    mapPtr[i] = new Object[width];
    for (int j = 0; j < width; j++) {
      mapPtr[i][j] = Object(i, j); //Create void at x, y
    }
  }
}