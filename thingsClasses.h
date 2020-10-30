#include <string>
#ifndef THINGSCLASSES_H
#define THINGSCLASSES_H
  enum class ObjectId { //Stores all ids of objects, starting with 0
    //all enums and const are capitalized
    VOID,
    FLOOR,
    TOPWALL,
    SIDEWALL,
    PLAYER,
    ROCK
  };
  enum class ObjectIcon { //Stores all icons (in ASCII character) of objects, mirrored with ObjectId
    VOID = ' ',
    FLOOR = '.',
    TOPWALL = '=',
    SIDEWALL = '|',
    PLAYER = '@',
    ROCK = '#'
  };
  class Point {
    public:
      int x, y;
      Point();
      Point(int px, int py);
      void changePos(int px, int py);
      int distanceTo(Point q); //Maybe return double
  };
  class Object { //Base Class for all objects
    public:
      ObjectId id; //special id
      ObjectIcon icon; //ASCII value
      Point pos;
      Object(); //create an empty object (the void)
      Object(int px, int py); //create an empth object at x, y
      Object(ObjectId Id, ObjectIcon Icon, int px, int py);
  };
  class Player : public Object { //The player
    public:
      int hp;
      std::string name;
      Player(std::string n, int px, int py);
      void movement(int dx, int dy);
  };
  class Rock : public Object {
    public:
      Rock(int px, int py);
      void moveRock(Point p);
  };
#endif
