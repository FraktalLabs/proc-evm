#pragma once

#include <iostream>
#include <map>

#include "opcodes.h"

class CallContext;

class Operation {
public:
  virtual void execute(CallContext&) = 0;
};

using JumpTable = std::map<Opcode, Operation*>; // TODO: use array instead of map since opcodes are contiguous uint8_t?

class StopOperation : public Operation {
public:
  void execute(CallContext&) override;
};

class AddOperation : public Operation {
public:
  void execute(CallContext&) override;
};

class MulOperation : public Operation {
public:
  void execute(CallContext&) override;
};

class SubOperation : public Operation {
public:
  void execute(CallContext&) override;
};

void StopOperation::execute(CallContext&) {
  std::cout << "STOP" << std::endl;
}

void AddOperation::execute(CallContext&) {
  std::cout << "ADD" << std::endl;
}

void MulOperation::execute(CallContext&) {
  std::cout << "MUL" << std::endl;
}

void SubOperation::execute(CallContext&) {
  std::cout << "SUB" << std::endl;
}

JumpTable jumpTable = {
  {Opcode::STOP, new StopOperation()},
  {Opcode::ADD, new AddOperation()},
  {Opcode::MUL, new MulOperation()},
  {Opcode::SUB, new SubOperation()}
};

Operation* getOperation(Opcode opcode) {
  return jumpTable[opcode];
}
