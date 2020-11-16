#include <iostream>

#include "winTile.h"
#include "colorIO.h"

WinTile::WinTile(int px, int py) : Object (ObjectId::WINTILE, ObjectIcon::WINTILE, px, py) {
  hasWon = false;
}
WinTile::WinTile(bool hw, int px, int py) : Object (ObjectId::WINTILE, ObjectIcon::WINTILE, px, py) {
  hasWon = hw;
}
void WinTile::process(Point p) {
  hasWon = true;
}
bool WinTile::check(Object *o) {

}
bool WinTile::isValid() {
  return true;
}
void WinTile::draw() {
  std::cout << addFGColor(FGCode::YELLOW) << addBGColor(BGCode::BRIGHT_YELLOW) << static_cast<char>(ObjectIcon::WINTILE) << reset();
}
