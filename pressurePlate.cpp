// Filename: pressurePlate.cpp
// Description: Program that implements the Snake class.
// Last Changed: 19 Nov, 2020
#include <iostream>

#include "pressurePlate.h"
#include "colorIO.h"
// Constructors for PressurePlate
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
// This function activates activateObj and itself
void PressurePlate::activate() {
  isPressed = true;
  if (activateObj != nullptr) {
    activateObj->open();
  }
}
// This function deactivates activateObj and itself
void PressurePlate::deactivate() {
  isPressed = false;
  if (activateObj != nullptr) {
    activateObj->close();
  }
}
// When PressurePlate is pressed it will activate
void PressurePlate::process(Point p) {
  this->activate();
}
bool PressurePlate::check(Object *o) {}
// PressurePlate can be pressed on
bool PressurePlate::isValid() {
  return true;
}
// PressurePlate has red background when not toggled, and green when toggled.
void PressurePlate::draw() {
  if (isPressed)
    std::cout << addBGColor(BGCode::GREEN) << reset();
  else
    std::cout << addFGColor(FGCode::BRIGHT_WHITE) << addBGColor(BGCode::BRIGHT_RED) << static_cast<char>(icon) << reset();
}
