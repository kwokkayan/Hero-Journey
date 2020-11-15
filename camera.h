//This draws the visible space of the player
//in a nxn box, centered on the player
#include "baseClasses.h"
#include "map.h"

#ifndef CAMERA_H
#define CAMERA_H
class Camera {
  public:
    int length;
    Point camera_pos;
    Camera();
    Camera(int l, Point p);
    void draw(Map m);
};
#endif
