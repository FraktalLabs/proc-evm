#pragma once

#include <memory>

#include "contract.h"
#include "memory.h"
#include "stack.h"

class CallContext {
public:
  CallContext(std::shared_ptr<Contract> contract, uint64_t pc)
      : contract(contract), pc(pc) {
    stack = std::make_unique<Stack>();
    memory = std::make_shared<Memory>();
  }

  uint64_t getPc() { return pc; }
  void setPc(uint64_t pc) { this->pc = pc; }
  void incPc() { pc++; }

  std::shared_ptr<Contract> getContract() { return contract; }
  std::unique_ptr<Stack> getStack() { return std::move(stack); } // TODO?
  std::shared_ptr<Memory> getMemory() { return memory; }

  void run(); // TODO: return value?

private:
  uint64_t pc;

  std::shared_ptr<Contract> contract;
  std::unique_ptr<Stack> stack; // TODO: shared or unique?
  std::shared_ptr<Memory> memory;
};
