// Filename: objectStack.cpp
// Description: Program that implements objectStack functions.
// Last Changed: 19 Nov, 2020
#include <iostream>

#include "objectStack.h"
#include "void.h"
// ObjectStack contructors
// index is initially defined as the last element, and each addition with decrement it,
// incrementing when removed
ObjectStack::ObjectStack() { // no depth defined, cannot create empty stack
  depth = 0;
  index = depth - 1;
  stack = nullptr;
}
ObjectStack::ObjectStack(int d) {
  depth = d;
  index = depth - 1;
  stack = new Object*[depth];
  for (int i = 0; i < depth; i++) { //empty stack of d length is defined
    stack[i] = new Void(); // The empty object: will not be displayed nor processed
  }
}
// This function releases all the Object pointers in the stack
void ObjectStack::deleteStack() {
  for (int i = 0; i < depth; i++) {
    delete stack[i];
  }
  delete[] stack;
}
// This function adds an Object to the last empty index of the stack
void ObjectStack::push(Object *o) {
  stack[index--] = o;
}
// This function removes the first Object from stack and return it
Object* ObjectStack::pop() {
  Object* temp = stack[++index];
  stack[index] = new Void();
  return temp;
}
// This function returns the first Object from the stack
Object* ObjectStack::top() {
  return stack[index + 1];
}
// This function returns the number of non-empty Objects in the stack
int ObjectStack::size() {
  return depth - index - 1;
}
