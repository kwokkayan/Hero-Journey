// Filename: openable.cpp
// Description: Program that implements the Openable class.
// Last Changed: 19 Nov, 2020
#include "openable.h"

//Constructors for Openable
Openable::Openable(ObjectId id, ObjectIcon icon, int px, int py) : Object (id, icon, px, py) {
  isOpened = false;
  activatorObj = nullptr;
}
Openable::Openable(bool io, Object *ao, ObjectId id, ObjectIcon icon, int px, int py) : Object (id, icon, px, py) {
  isOpened = io;
  activatorObj = ao;
}
// This is used for opening the openable
void Openable::open() {}
// This is used for closing the openable
void Openable::close() {}
