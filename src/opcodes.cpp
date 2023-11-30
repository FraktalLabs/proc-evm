#include <map>

#include "opcodes.h"

std::map<Opcode, std::string> opcodeStrings = {
    {Opcode::STOP, "STOP"},
    {Opcode::ADD, "ADD"},
    {Opcode::MUL, "MUL"},
    {Opcode::SUB, "SUB"},
    {Opcode::MSTORE, "MSTORE"},
    {Opcode::MLOAD, "MLOAD"},
    {Opcode::PUSH1, "PUSH1"}
};

std::string opcodeToString(Opcode opcode) {
  return opcodeStrings[opcode];
};
