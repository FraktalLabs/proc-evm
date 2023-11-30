#include <iostream>

#include "stack.h"

uint256 Stack::pop() {
  return stack[--stack_len];
}

uint256& Stack::peek() {
  return stack[len() - 1];
}

void Stack::push(uint256 value) {
  stack[stack_len++] = value;
}

uint64_t Stack::len() {
  return stack_len;
}

void Stack::swap(uint64_t n) {
  uint256 tmp = stack[len() - n];
  stack[len() - n] = stack[len() - 1];
  stack[len() - 1] = tmp;
}

void Stack::dup(uint64_t n) {
  stack[len()] = stack[len() - n];
  stack_len++;
}

std::string Stack::toString() {
  std::string result = "";
  for (uint64_t i = 0; i < len(); i++) {
    result += "0x" + to_string(stack[i], 16) + " "; // TODO: pad to 256 bits
  }
  return result;
}
