#ifndef COLORIO_H
#define COLORIO_H
  enum class FGCode { //30.. 37
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
