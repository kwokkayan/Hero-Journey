// Filename: thingsClasses.h
// Description: Header file for thingsClasses, stores declarations for object-related classes
// Last Changed: 5 Nov, 2020

// *********************************
// TODO: REFACTOR THE CODE ARRRRRRRR
// *********************************

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
    ZOMBIE
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
    ZOMBIE = 'Z'
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
      virtual void process(Point p);
      virtual bool check(Object *o); //used for checking the next object 0 for ok 1 for not ok 2 for further check
      virtual bool isValid();
      virtual void draw();
  };
#endif
