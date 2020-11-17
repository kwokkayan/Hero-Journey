#include "openable.h"

Openable::Openable(ObjectId id, ObjectIcon icon, int px, int py) : Object (id, icon, px, py) {
  isOpened = false;
  activatorObj = nullptr;
}
Openable::Openable(bool io, Object *ao, ObjectId id, ObjectIcon icon, int px, int py) : Object (id, icon, px, py) {
  isOpened = io;
  activatorObj = ao;
}
void Openable::open() {}
void Openable::close() {}
