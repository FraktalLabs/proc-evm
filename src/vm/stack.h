#pragma once

#include <intx/intx.hpp>   

using uint256 = intx::uint256;

class Stack {
public:
  uint256 pop();
  uint256& peek();
  void push(uint256 value);
  uint64_t len();
  void swap(uint64_t n);
  void dup(uint64_t n);

  std::string toString();
private:
  alignas(sizeof(uint256)) uint256 stack[1024];
  uint64_t stack_len = 0;
};
