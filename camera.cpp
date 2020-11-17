// This handles the camera and prints the map
//
//
//
#include <iostream>

#include "camera.h"
#include "colorIO.h"
#include "gameFunctions.h"

Camera::Camera() {
  length = 0;
  camera_pos = Point(0, 0);
}
Camera::Camera(int l, Point p) {
  length = l;
  camera_pos = p;
}
void Camera::draw(Map m) {
  int alignWidth = 30; //change to class
  Point camera_topleft = Point(
    camera_pos.x - length / 2,
    camera_pos.y - length / 2
  );

  game_func::setFormat(alignWidth);
  for (int k = 0; k < length + 2; k++)
    std::cout << '~';
  std::cout << '\n';
  for (int i = camera_topleft.y; i < camera_topleft.y + length; i++) {
    game_func::setFormat(alignWidth);
    std::cout << '~';
    for (int j = camera_topleft.x; j < camera_topleft.x + length; j++) {
      //TODO: DONT USE ENUMS
      //THEY ARE HORRIBLE
      if ((i < 0 || i >= m.getHeight()) || (j < 0 || j >= m.getWidth()))
        std::cout << addBGColor(BGCode::BLACK) << static_cast<char>(ObjectIcon::VOID) << reset(); //ENUM CASTING
      else //PRINTING MAP OBJECTS
        m.getObject(j, i)->draw();
    }
    std::cout << "~\n";
  }
  game_func::setFormat(alignWidth);
  for (int k = 0; k < length + 2; k++)
    std::cout << '~';
  std::cout << '\n';
}
