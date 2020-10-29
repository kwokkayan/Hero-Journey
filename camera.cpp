#include <iostream>
#include "camera.h"
Camera::Camera() {
  length = 0;
  camera_pos = Point(0, 0);
}
Camera::Camera(int l, Point p) {
  length = l;
  camera_pos = p;
}
void Camera::draw(Map m) {
  Point camera_topleft = Point(
    camera_pos.x - length / 2,
    camera_pos.y - length / 2
  );

  for (int k = 0; k < length; k++)
    std::cout << '=';
  std::cout << '\n';
  for (int i = camera_topleft.y; i < camera_topleft.y + length; i++) {
    std::cout << '|';
    for (int j = camera_topleft.x; i < camera_topleft.x + length; j++) {
      //TODO: DONT USE ENUMS
      //THEY ARE HORRIBLE
      if ((i < 0 || i > m.getHeight()) && (j < 0 || j > m.getWidth()))
        std::cout << static_cast<char>(ObjectIcon::VOID); //ENUM CASTING
      else
        std::cout << static_cast<char>(m.getObject(j, i).icon);
    }
    std::cout << '|\n';
  }
  for (int k = 0; k < length; k++)
    std::cout << '=';
  std::cout << '\n';
}