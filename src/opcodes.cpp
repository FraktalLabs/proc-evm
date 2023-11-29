#include <map>

#include "opcodes.h"

std::map<Opcode, std::string> opcodeStrings = {
    {Opcode::STOP, "STOP"},
    {Opcode::ADD, "ADD"},
    {Opcode::MUL, "MUL"},
    {Opcode::SUB, "SUB"}
};

std::string opcodeToString(Opcode opcode) {
  return opcodeStrings[opcode];
};
