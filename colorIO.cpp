#include <string>
#include <iostream>
#include "colorIO.h"
// For the four functions, the ANSI escape code is used.
// By adding the correct code, the color or modifyer can be achieved.
std::string addFGColor(FGCode color) {
  std::string cStr = std::to_string(static_cast<int>(color));
  return "\033[" + cStr + "m";
}
std::string addBGColor(BGCode color) {
  std::string cStr = std::to_string(static_cast<int>(color));
  return "\033[" + cStr + "m";
}
std::string addModifyer(Modifyer modifyer) {
  std::string mStr = std::to_string(static_cast<int>(modifyer));
  return "\033[" + mStr + "m";
}
// This function erases the color or modifyer
std::string reset() {
  return "\033[0m";
}
