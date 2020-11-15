#include "baseClasses.h"
#ifndef OBJECTSTACK_H
#define OBJECTSTACK_H
  class ObjectStack {
    private:
      int depth;
      int index;
      Object **stack;
    public:
      ObjectStack();
      ObjectStack(int d);
      void push(Object *o);
      Object* pop();
      Object* top();
      int size();
  };
#endif
