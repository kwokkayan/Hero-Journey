#include "openable.h"

Openable::Openable(ObjectId id, ObjectIcon icon, int px, int py) : Object (id, icon, px, py) {
  isOpened = false;
  activatorObj = nullptr;
}
void Openable::open() {}
void Openable::close() {}
