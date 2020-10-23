#include <string>
#ifndef THINGSCLASSES_H
#define THINGSCLASSES_H
  class Point {
    private:
      int x, y;
    public:
      Point();
      Point(int px, int py);
      int getX();
      int getY();
      void changePos(int px, int py);
      int distanceTo(Point q); //Maybe return double
  };
  class Object { //Base Class for all objects
    private:
      int id; //special id
      char icon; //ASCII value
      Point pos;
    public:
      Object(); //create an empty object (the void)
      Object(int px, int py); //create an empth object at x, y
      Object(int Id, char Icon, int px, int py);
      int getId();
      char getIcon();
  };
  class Player : public Object { //The player
    private:
      int hp;
      std::string name;
    public:
      Player();
      Player(std::string name, int px, int py);
      void movement();
  };
  class Rock : public Object {
    public:
      Rock(int Id, char Icon, int px, int py);
      void moveRock(Point p);
  };
#endif