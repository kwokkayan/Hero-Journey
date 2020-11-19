// Filename: colorIO.h
// Description: Header that declares frontground color codes, background color codes, modifyer codes, and color text function.
// Last Changed: 19 Nov, 2020
#ifndef COLORIO_H
#define COLORIO_H
  // color codes are taken from the following wiki article:
  // https://en.wikipedia.org/wiki/ANSI_escape_code
  // FGCode enum defines the frontground color code
  // BGCode enum defines the background color code
  // Modifyer enum defines the modifyer codes
  enum class FGCode {
    BLACK = 30,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
    BRIGHT_BLACK = 90,
    BRIGHT_RED,
    BRIGHT_GREEN,
    BRIGHT_YELLOW,
    BRIGHT_BLUE,
    BRIGHT_MAGENTA,
    BRIGHT_CYAN,
    BRIGHT_WHITE
  };
  enum class BGCode {
    BLACK = 40,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
    BRIGHT_BLACK = 100,
    BRIGHT_RED,
    BRIGHT_GREEN,
    BRIGHT_YELLOW,
    BRIGHT_BLUE,
    BRIGHT_MAGENTA,
    BRIGHT_CYAN,
    BRIGHT_WHITE
  };
  enum class Modifyer {
    RESET = 0,
    BOLD = 1,
    UNDERLINE = 4,
    INVERSE = 7,
    NOBOLD = 21,
    NOUNDERLINE = 24,
    NOINVERSE = 27
  };
  std::string addFGColor(FGCode color);
  std::string addBGColor(BGCode color);
  std::string addModifyer(Modifyer modifyer);
  std::string reset();
#endif
