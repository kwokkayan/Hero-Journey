#include "objectStack.h"
ObjectStack::ObjectStack() {
  depth = 0;
  index = depth - 1;
  stack = nullptr;
}
ObjectStack::ObjectStack(int d) {
  depth = d;
  index = depth - 1;
  stack = new Object[depth];
  for (int i = 0; i < depth; i++) {
    stack[i] = Object();
  }
}
void ObjectStack::push(Object o) {
  stack[index--] = o;
}
Object ObjectStack::pop() {
  Object temp = stack[index + 1];
  stack[index++] = Object();
  return temp;
}
Object ObjectStack::top() {
  return stack[index + 1]; //shit code
}
int ObjectStack::size() {
  return depth - index - 1;
}
