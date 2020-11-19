// Filename: baseClasses.h
// Description: Header that declares the enums and base classes.
// Last Changed: 19 Nov, 2020
#include <vector>

#ifndef BASECLASSES_H
#define BASECLASSES_H
  // ObjectId stores all ids of objects, starting with 0
  enum class ObjectId {
    //all enums and const are capitalized
    VOID,
    FLOOR,
    TOPWALL,
    SIDEWALL,
    PLAYER,
    ROCK,
    PRESSUREPLATE,
    DOOR,
    ZOMBIE,
    SNAKE,
    WINTILE,
    INFOTILE,
  };
  // ObjectIcon stores all icons (in ASCII character) of objects, mirrored with ObjectId
  enum class ObjectIcon {
    VOID = ' ',
    FLOOR = '.',
    TOPWALL = '=',
    SIDEWALL = '|',
    PLAYER = '@',
    ROCK = '#',
    PRESSUREPLATE = '*',
    DOOR = '+',
    ZOMBIE = 'Z',
    SNAKE = 'S',
    WINTILE = '.',
    INFOTILE = '!'
  };
  // Point stores the Cartesian coordinates of all objects
  // and functions that manipulate them
  class Point {
    public:
      int x, y;
      Point();
      Point(int px, int py);
      void changePos(int px, int py);
      int distanceTo(Point p); //Maybe return double
      std::vector<Point> closestPointsTo(Point p, int vd);
      bool equalsTo(Point p);
      bool equalsTo(int px, int py);
  };
  // Object is the base class of all objects
  // Every object has an id, icon and pos.
  // Id is used for identitfying the object type
  // Icon is used for displaying the objects
  // pos stores the xy position of the objects
  class Object {
    public:
      ObjectId id; //special id
      ObjectIcon icon; //ASCII value
      Point pos;
      Object(); //create an empty object (the void)
      Object(int px, int py); //create an empty object at x, y
      Object(ObjectId Id, ObjectIcon Icon, int px, int py);
      // All object can implement these functions
      virtual void process(Point p); // Used for processing the object after player or mob movement
      virtual bool check(Object *o); // Used for checking valid movement for player and mobs
      virtual bool isValid(); // Used for checking whether the object is a valid spot to move to
      virtual void draw(); // Used for drawing the object
  };
#endif
