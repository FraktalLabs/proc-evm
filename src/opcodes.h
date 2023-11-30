#pragma once

//TODO: pragma once(s) and namespace(s)
#include <stdint.h>
#include <string>

enum Opcode : uint8_t {
  STOP = 0x00,
  ADD = 0x01,
  MUL = 0x02,
  SUB = 0x03,

  MSTORE = 0x04,
  MLOAD = 0x05,

  JUMP = 0x06,
  JUMPDEST = 0x07,

  PUSH1 = 0x60,
  PUSH2 = 0x61,
  PUSH3 = 0x62,
  PUSH4 = 0x63,
  PUSH5 = 0x64,
  PUSH6 = 0x65,
  PUSH7 = 0x66,
  PUSH8 = 0x67,
  PUSH9 = 0x68,
  PUSH10 = 0x69,
  PUSH11 = 0x6a,
  PUSH12 = 0x6b,
  PUSH13 = 0x6c,
  PUSH14 = 0x6d,
  PUSH15 = 0x6e,
  PUSH16 = 0x6f,
  PUSH17 = 0x70,
  PUSH18 = 0x71,
  PUSH19 = 0x72,
  PUSH20 = 0x73,
  PUSH21 = 0x74,
  PUSH22 = 0x75,
  PUSH23 = 0x76,
  PUSH24 = 0x77,
  PUSH25 = 0x78,
  PUSH26 = 0x79,
  PUSH27 = 0x7a,
  PUSH28 = 0x7b,
  PUSH29 = 0x7c,
  PUSH30 = 0x7d,
  PUSH31 = 0x7e,
  PUSH32 = 0x7f,

};

std::string opcodeToString(Opcode opcode);
