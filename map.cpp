#include "map.h"
Map::Map() {
  width = 0;
  height = 0;
  mapPtr = nullptr;
}
void Map::createEmptyMap(int w, int h, int depth) {
  width = w;
  height = h;
  mapPtr = new ObjectStack*[height];
  for (int i = 0; i < height; i++) {
    mapPtr[i] = new ObjectStack[width];
    for (int j = 0; j < width; j++) {
      mapPtr[i][j] = ObjectStack(depth);
      if ((i > 0 || i < height) && (j == 0 || j == width - 1))
        mapPtr[i][j].push(Object(ObjectId::SIDEWALL, ObjectIcon::SIDEWALL, j, i));
      else if (i == 0 || i == height - 1)
        mapPtr[i][j].push(Object(ObjectId::TOPWALL, ObjectIcon::TOPWALL, j, i));
      else
        mapPtr[i][j].push(Object(ObjectId::FLOOR, ObjectIcon::FLOOR, j, i));
    }
  }
}
void Map::deleteMap() {
  for (int i = 0; i < height; i++) {
    delete[] mapPtr[i];
  }
  delete[] mapPtr;
}
// A bit stupid - maybe just integrate the stack
void Map::insertObject(Object o, int px, int py) {
  mapPtr[py][px].push(o); //TODO: ERROR HANDLING
}
void Map::insertObject(Object o, Point p) {
  mapPtr[p.y][p.x].push(o); //TODO: ERROR HANDLING
}
Object Map::removeObject(int px, int py) {
  return mapPtr[py][px].pop();
}
Object Map::removeObject(Point p) {
  return mapPtr[p.y][p.x].pop();
}
Object Map::getObject(int px, int py) {
  return mapPtr[py][px].top();
}
Object Map::getObject(Point p) {
  return mapPtr[p.y][p.x].top();
}

int Map::getWidth() { return width; }
int Map::getHeight() { return height; }
