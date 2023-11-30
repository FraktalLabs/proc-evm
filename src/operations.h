#pragma once

#include <iostream>
#include <map>

#include "opcodes.h"
#include "call_context.h"

enum ExecStatus {
  CONTINUE,
  STOPEXEC // TODO: rename to STOP
};

class Operation {
public:
  virtual ExecStatus execute(CallContext&) = 0;
};

using JumpTable = std::map<Opcode, Operation*>; // TODO: use array instead of map since opcodes are contiguous uint8_t?

class StopOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class AddOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class MulOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class SubOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class MstoreOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class MloadOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class Push1Operation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class JumpOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

class JumpdestOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

ExecStatus StopOperation::execute(CallContext&) {
  return STOPEXEC;
}

ExecStatus AddOperation::execute(CallContext& context) {
  uint256 x = context.getStack()->pop();
  uint256& y = context.getStack()->peek();
  y += x;

  return CONTINUE;
}

ExecStatus MulOperation::execute(CallContext& context) {
  uint256 x = context.getStack()->pop();
  uint256& y = context.getStack()->peek();
  y *= x;

  return CONTINUE;
}

ExecStatus SubOperation::execute(CallContext& context) {
  uint256 x = context.getStack()->pop();
  uint256& y = context.getStack()->peek();
  y -= x;

  return CONTINUE;
}

ExecStatus MstoreOperation::execute(CallContext& context) {
  uint256 memStart = context.getStack()->pop();
  uint256 value = context.getStack()->pop();
  context.getMemory()->store32(static_cast<uint64_t>(memStart), static_cast<uint32_t>(value));

  return CONTINUE;
}

ExecStatus MloadOperation::execute(CallContext& context) {
  uint256& value = context.getStack()->peek();
  uint64_t offset = static_cast<uint64_t>(value);
  uint256 memValue = context.getMemory()->load32(offset);
  value = memValue;

  return CONTINUE;
}

ExecStatus Push1Operation::execute(CallContext& context) {
  uint64_t codeLen = context.getContract()->getBytecodeSize();
  context.incPc();

  if (context.getPc() < codeLen) {
    context.getStack()->push(context.getContract()->getBytecodeAt(context.getPc()));
  } else {
    context.getStack()->push(0);
  }

  return CONTINUE;
}

ExecStatus JumpOperation::execute(CallContext& context) {
  uint256 jumpDest = context.getStack()->pop();
  // TODO: jump to 0?
  if(!(context.getContract()->getBytecodeAt(static_cast<uint64_t>(jumpDest)) == Opcode::JUMPDEST)) {
    std::cout << "Invalid jump destination at dest : " << to_string(jumpDest, 10) << " operation : " << opcodeToString(context.getContract()->getOpcodeAt(static_cast<uint64_t>(jumpDest))) << std::endl;
    return STOPEXEC;
  }
  context.setPc(static_cast<uint64_t>(jumpDest) - 1); // -1 because pc is incremented after each instruction

  return CONTINUE;
}

ExecStatus JumpdestOperation::execute(CallContext& context) {
  return CONTINUE;
}

JumpTable jumpTable = {
  {Opcode::STOP, new StopOperation()},
  {Opcode::ADD, new AddOperation()},
  {Opcode::MUL, new MulOperation()},
  {Opcode::SUB, new SubOperation()},
  {Opcode::MSTORE, new MstoreOperation()},
  {Opcode::MLOAD, new MloadOperation()},
  {Opcode::PUSH1, new Push1Operation()},
  {Opcode::JUMP, new JumpOperation()},
  {Opcode::JUMPDEST, new JumpdestOperation()}
};

Operation* getOperation(Opcode opcode) {
  return jumpTable[opcode];
}
