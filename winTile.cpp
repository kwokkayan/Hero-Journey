// Filename: winTile.cpp
// Description: Program that implements the winTile class.
// Last Changed: 19 Nov, 2020
#include <iostream>

#include "winTile.h"
#include "colorIO.h"

WinTile::WinTile(int px, int py) : Object (ObjectId::WINTILE, ObjectIcon::WINTILE, px, py) {
  hasWon = false;
}
WinTile::WinTile(bool hw, int px, int py) : Object (ObjectId::WINTILE, ObjectIcon::WINTILE, px, py) {
  hasWon = hw;
}
// When player steps on wintile, the game has won, and so the flag is set to true.
void WinTile::process(Point p) {
  hasWon = true;
}
bool WinTile::check(Object *o) {

}
// Player can step on winTile
bool WinTile::isValid() {
  return true;
}
void WinTile::draw() {
  std::cout << addFGColor(FGCode::YELLOW) << addBGColor(BGCode::BRIGHT_YELLOW) << static_cast<char>(ObjectIcon::WINTILE) << reset();
}
