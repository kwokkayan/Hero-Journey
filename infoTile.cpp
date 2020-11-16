#include <iostream>
#include <fstream>

#include "infoTile.h"
#include "gameFunctions.h"
#include "colorIO.h"

InfoTile::InfoTile(std::string address, int px, int py) : Object (ObjectId::INFOTILE, ObjectIcon::INFOTILE, px, py) {
  info = "";
  std::ifstream fin;
  fin.open(address);
  std::string s;
  while (getline(fin, s)) {
    info += s + '\n';
  }
}
void InfoTile::process(Point p) {
  std::string s;
  game_func::clrScr(100);
  std::cout << "The info tile reads:\n";
  std::cout << info;
  std::cout << "Press enter to continue...";
  getline(std::cin, s);
}
bool InfoTile::check(Object *o) {

}
bool InfoTile::isValid() {
  return true;
}
void InfoTile::draw() {
  std::cout << addFGColor(FGCode::BLUE) << addBGColor(BGCode::BRIGHT_BLUE) << static_cast<char>(ObjectIcon::INFOTILE) << reset();
}
