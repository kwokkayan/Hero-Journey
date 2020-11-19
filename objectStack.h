// Filename: objectStack.h
// Description: Header that declares the ObjectStack class.
// Last Changed: 19 Nov, 2020
#include "baseClasses.h"
#ifndef OBJECTSTACK_H
#define OBJECTSTACK_H
  // ObjectStack is a stack for objects (first in first out)
  // depth is the length of the pointer array stack
  // while index is defined as the index of stack of the top object, which is the newest added object
  // comments for functions are in objectStack.cpp
  class ObjectStack {
    private:
      int depth;
      int index;
      Object **stack;
    public:
      ObjectStack();
      ObjectStack(int d);
      void deleteStack();
      void push(Object *o);
      Object* pop();
      Object* top();
      int size();
  };
#endif
