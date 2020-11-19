// Filename: infoTile.cpp
// Description: Program that implements the infoTile class.
// Last Changed: 19 Nov, 2020
#include <iostream>
#include <fstream>

#include "infoTile.h"
#include "gameFunctions.h"
#include "colorIO.h"
// Constructor for InfoTile
// The file given by address is opened and the text is stored in a string
// for later use.
InfoTile::InfoTile(std::string a, int px, int py) : Object (ObjectId::INFOTILE, ObjectIcon::INFOTILE, px, py) {
  info = "";
  address = a;
  std::ifstream fin;
  fin.open(address);
  if (fin.is_open()) {
    std::string s;
    while (getline(fin, s)) {
      info += s + '\n';
    }
  }
}
// This function prints the infomation when the player steps on the tile
void InfoTile::process(Point p) {
  std::string s;
  game_func::clrScr(100);
  std::cout << "The info tile reads:\n";
  std::cout << info;
  std::cout << "Press any key to continue...";
  char temp = game_func::getKeystroke();
}
bool InfoTile::check(Object *o) {

}
// Player can step on infotile
bool InfoTile::isValid() {
  return true;
}
void InfoTile::draw() {
  std::cout << addFGColor(FGCode::BLUE) << addBGColor(BGCode::BRIGHT_BLUE) << static_cast<char>(ObjectIcon::INFOTILE) << reset();
}
