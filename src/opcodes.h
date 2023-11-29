#pragma once

//TODO: pragma once(s) and namespace(s)
#include <stdint.h>
#include <string>

enum Opcode : uint8_t {
  STOP = 0x00,
  ADD = 0x01,
  MUL = 0x02,
  SUB = 0x03,

  PUSH1 = 0x04
};

std::string opcodeToString(Opcode opcode);
