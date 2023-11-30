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

template <uint8_t N>
class PushNOperation : public Operation {
public:
  ExecStatus execute(CallContext&) override;
};

template <uint8_t N>
class DupNOperation : public Operation {
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

template <uint8_t N>
ExecStatus PushNOperation<N>::execute(CallContext& context) {
  uint64_t codeLen = context.getContract()->getBytecodeSize();

  uint64_t start = codeLen;
  if (context.getPc() + 1 < codeLen) {
    start = context.getPc() + 1;
  }

  // TODO: wouldn't this cause a bug at end of code?
  uint64_t end = codeLen;
  if (start + N < codeLen) {
    end = start + N;
  }

  uint256 value = 0;
  for (uint64_t i = start; i < end; i++) {
    value = (value << 8) + context.getContract()->getBytecodeAt(i);
  }

  context.setPc(context.getPc() + N);
  context.getStack()->push(value);

  return CONTINUE;
}

template <uint8_t N>
ExecStatus DupNOperation<N>::execute(CallContext& context) {
  context.getStack()->dup(N);

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
  {Opcode::JUMP, new JumpOperation()},
  {Opcode::JUMPDEST, new JumpdestOperation()},
  {Opcode::PUSH1, new Push1Operation()},
  {Opcode::PUSH2, new PushNOperation<2>()},
  {Opcode::PUSH3, new PushNOperation<3>()},
  {Opcode::PUSH4, new PushNOperation<4>()},
  {Opcode::PUSH5, new PushNOperation<5>()},
  {Opcode::PUSH6, new PushNOperation<6>()},
  {Opcode::PUSH7, new PushNOperation<7>()},
  {Opcode::PUSH8, new PushNOperation<8>()},
  {Opcode::PUSH9, new PushNOperation<9>()},
  {Opcode::PUSH10, new PushNOperation<10>()},
  {Opcode::PUSH11, new PushNOperation<11>()},
  {Opcode::PUSH12, new PushNOperation<12>()},
  {Opcode::PUSH13, new PushNOperation<13>()},
  {Opcode::PUSH14, new PushNOperation<14>()},
  {Opcode::PUSH15, new PushNOperation<15>()},
  {Opcode::PUSH16, new PushNOperation<16>()},
  {Opcode::PUSH17, new PushNOperation<17>()},
  {Opcode::PUSH18, new PushNOperation<18>()},
  {Opcode::PUSH19, new PushNOperation<19>()},
  {Opcode::PUSH20, new PushNOperation<20>()},
  {Opcode::PUSH21, new PushNOperation<21>()},
  {Opcode::PUSH22, new PushNOperation<22>()},
  {Opcode::PUSH23, new PushNOperation<23>()},
  {Opcode::PUSH24, new PushNOperation<24>()},
  {Opcode::PUSH25, new PushNOperation<25>()},
  {Opcode::PUSH26, new PushNOperation<26>()},
  {Opcode::PUSH27, new PushNOperation<27>()},
  {Opcode::PUSH28, new PushNOperation<28>()},
  {Opcode::PUSH29, new PushNOperation<29>()},
  {Opcode::PUSH30, new PushNOperation<30>()},
  {Opcode::PUSH31, new PushNOperation<31>()},
  {Opcode::PUSH32, new PushNOperation<32>()},
  {Opcode::DUP1, new DupNOperation<1>()},
  {Opcode::DUP2, new DupNOperation<2>()},
  {Opcode::DUP3, new DupNOperation<3>()},
  {Opcode::DUP4, new DupNOperation<4>()},
  {Opcode::DUP5, new DupNOperation<5>()},
  {Opcode::DUP6, new DupNOperation<6>()},
  {Opcode::DUP7, new DupNOperation<7>()},
  {Opcode::DUP8, new DupNOperation<8>()},
  {Opcode::DUP9, new DupNOperation<9>()},
  {Opcode::DUP10, new DupNOperation<10>()},
  {Opcode::DUP11, new DupNOperation<11>()},
  {Opcode::DUP12, new DupNOperation<12>()},
  {Opcode::DUP13, new DupNOperation<13>()},
  {Opcode::DUP14, new DupNOperation<14>()},
  {Opcode::DUP15, new DupNOperation<15>()},
  {Opcode::DUP16, new DupNOperation<16>()},
};

Operation* getOperation(Opcode opcode) {
  return jumpTable[opcode];
}
