#include <iostream>

#include "objectStack.h"

ObjectStack::ObjectStack() {
  depth = 0;
  index = depth - 1;
  stack = nullptr;
}
ObjectStack::ObjectStack(int d) {
  depth = d;
  index = depth - 1;
  stack = new Object*[depth]; //error
  for (int i = 0; i < depth; i++) {
    stack[i] = new Object();
  }
}
void ObjectStack::push(Object *o) {
  //std::cout << o << "\n";
  stack[index--] = o;
  //std::cout << "object icon: " << static_cast<char>(stack[index+1]->icon) << "\n";
}
Object* ObjectStack::pop() {
  Object* temp = stack[index + 1];
  stack[index++] = new Object();
  return temp;
}
Object* ObjectStack::top() {
  //std::cout << stack[index + 1] << "\n";
  return stack[index + 1]; //shit code
}
int ObjectStack::size() {
  return depth - index - 1;
}