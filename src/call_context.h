#pragma once

#include <memory>

#include "contract.h"
#include "memory.h"
#include "stack.h"

#include "state/state.h"

class CallContext {
public:
  CallContext(std::shared_ptr<Contract> contract, uint64_t pc)
      : contract(contract), pc(pc) {
    stack = std::make_unique<Stack>();
    memory = std::make_shared<Memory>();
    state = std::make_shared<State>();
  }
  CallContext(std::shared_ptr<Contract> contract, uint64_t pc, std::shared_ptr<State> state)
      : contract(contract), pc(pc), state(state) {
    stack = std::make_unique<Stack>();
    memory = std::make_shared<Memory>();
  }
  CallContext(std::shared_ptr<Contract> contract, uint64_t pc, std::shared_ptr<State> state, const std::string& callAddress)
      : contract(contract), pc(pc), state(state) {
    contract->setAddress(callAddress);
    stack = std::make_unique<Stack>();
    memory = std::make_shared<Memory>();
  }

  uint64_t getPc() { return pc; }
  void setPc(uint64_t pc) { this->pc = pc; }
  void incPc() { pc++; }

  std::shared_ptr<Contract> getContract() { return contract; }
  std::shared_ptr<Stack> getStack() { return stack; } // TODO?
  std::shared_ptr<Memory> getMemory() { return memory; }
  std::shared_ptr<State> getState() { return state; }

  void run(); // TODO: return value?

private:
  uint64_t pc;

  std::shared_ptr<Contract> contract;
  std::shared_ptr<Stack> stack; // TODO: shared or unique?
  std::shared_ptr<Memory> memory;
  std::shared_ptr<State> state;
};
