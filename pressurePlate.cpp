#include <iostream>

#include "pressurePlate.h"
#include "colorIO.h"
PressurePlate::PressurePlate(int px, int py) : Object(ObjectId::PRESSUREPLATE, ObjectIcon::PRESSUREPLATE, px, py) {
  isPressed = false;
  activateObj = nullptr;
}
PressurePlate::PressurePlate(bool ip, Openable *ao, int px, int py) : Object(ObjectId::PRESSUREPLATE, ObjectIcon::PRESSUREPLATE, px, py) {
  isPressed = ip;
  activateObj = ao;
}
PressurePlate::PressurePlate(bool ip, int px, int py) : Object(ObjectId::PRESSUREPLATE, ObjectIcon::PRESSUREPLATE, px, py) {
  isPressed = ip;
}
void PressurePlate::activate() {
  isPressed = true;
  if (activateObj != nullptr) {
    activateObj->open();
  }
}
void PressurePlate::deactivate() {
  isPressed = false;
  std::cout << activateObj;
  if (activateObj != nullptr) {
    activateObj->close();
  }
}
void PressurePlate::process(Point p) {
  this->activate();
}
bool PressurePlate::check(Object *o) {
  //idk
}
bool PressurePlate::isValid() {
  return true;
}
void PressurePlate::draw() {
  if (isPressed)
    std::cout << addBGColor(BGCode::GREEN) << static_cast<char>(icon) << reset();
  else
    std::cout << addFGColor(FGCode::BRIGHT_WHITE) << addBGColor(BGCode::BRIGHT_RED) << static_cast<char>(icon) << reset();
}
