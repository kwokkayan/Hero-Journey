#include <string>
#include <iostream>
#include "colorIO.h"
std::string addFGColor(FGCode color) {
  std::string cStr = std::to_string(static_cast<int>(color));
  //std::cout << static_cast<int>(color) << "\n";
  return "\033[" + cStr + "m";
}
std::string addBGColor(BGCode color) {
  std::string cStr = std::to_string(static_cast<int>(color));
  //std::cout << cStr << "\n";
  return "\033[" + cStr + "m";
}
std::string addModifyer(Modifyer modifyer) {
  std::string mStr = std::to_string(static_cast<int>(modifyer));
  return "\033[" + mStr + "m";
}
std::string reset() {
  return "\033[0m";
}
