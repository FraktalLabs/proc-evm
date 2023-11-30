#include <map>

#include "opcodes.h"

std::map<Opcode, std::string> opcodeStrings = {
    {Opcode::STOP, "STOP"},
    {Opcode::ADD, "ADD"},
    {Opcode::MUL, "MUL"},
    {Opcode::SUB, "SUB"},
    {Opcode::JUMP, "JUMP"},
    {Opcode::JUMPDEST, "JUMPDEST"},
    {Opcode::MSTORE, "MSTORE"},
    {Opcode::MLOAD, "MLOAD"},

    {Opcode::PUSH1, "PUSH1"},
    {Opcode::PUSH2, "PUSH2"},
    {Opcode::PUSH3, "PUSH3"},
    {Opcode::PUSH4, "PUSH4"},
    {Opcode::PUSH5, "PUSH5"},
    {Opcode::PUSH6, "PUSH6"},
    {Opcode::PUSH7, "PUSH7"},
    {Opcode::PUSH8, "PUSH8"},
    {Opcode::PUSH9, "PUSH9"},
    {Opcode::PUSH10, "PUSH10"},
    {Opcode::PUSH11, "PUSH11"},
    {Opcode::PUSH12, "PUSH12"},
    {Opcode::PUSH13, "PUSH13"},
    {Opcode::PUSH14, "PUSH14"},
    {Opcode::PUSH15, "PUSH15"},
    {Opcode::PUSH16, "PUSH16"},
    {Opcode::PUSH17, "PUSH17"},
    {Opcode::PUSH18, "PUSH18"},
    {Opcode::PUSH19, "PUSH19"},
    {Opcode::PUSH20, "PUSH20"},
    {Opcode::PUSH21, "PUSH21"},
    {Opcode::PUSH22, "PUSH22"},
    {Opcode::PUSH23, "PUSH23"},
    {Opcode::PUSH24, "PUSH24"},
    {Opcode::PUSH25, "PUSH25"},
    {Opcode::PUSH26, "PUSH26"},
    {Opcode::PUSH27, "PUSH27"},
    {Opcode::PUSH28, "PUSH28"},
    {Opcode::PUSH29, "PUSH29"},
    {Opcode::PUSH30, "PUSH30"},
    {Opcode::PUSH31, "PUSH31"},
    {Opcode::PUSH32, "PUSH32"}
};

std::string opcodeToString(Opcode opcode) {
  return opcodeStrings[opcode];
};
