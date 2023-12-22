#pragma once

#include <memory>

#include "contract.h"
#include "memory.h"
#include "stack.h"
#include "block_context.h"
#include "tx_context.h"
#include "state/state.h"

class CallContext {
public:
  CallContext(std::shared_ptr<Contract> contract, uint64_t pc)
      : contract(contract), pc(pc), value(0), input(), caller() {
    stack = std::make_unique<Stack>();
    memory = std::make_shared<Memory>();
    state = std::make_shared<State>();
    blockContext = std::make_shared<BlockContext>();
    txContext = std::make_shared<TxContext>();
  }
  CallContext(std::shared_ptr<Contract> contract, uint64_t pc, std::shared_ptr<State> state)
      : contract(contract), caller(), pc(pc), value(0), input(), state(state) {
    stack = std::make_unique<Stack>();
    memory = std::make_shared<Memory>();
    blockContext = std::make_shared<BlockContext>();
    txContext = std::make_shared<TxContext>();
  }
  CallContext(std::shared_ptr<Contract> contract, uint64_t pc, std::shared_ptr<State> state,const std::string& callAddress)
      : contract(contract), caller(), pc(pc), value(0), input(), state(state) {
    contract->setAddress(callAddress);
    stack = std::make_unique<Stack>();
    memory = std::make_shared<Memory>();
    blockContext = std::make_shared<BlockContext>();
    txContext = std::make_shared<TxContext>();
  }
  //TODO: Pass specific context & caller?, value, input
  CallContext(std::shared_ptr<Contract> contract, intx::uint256 value, bytes input, address caller,
              std::shared_ptr<State> state, std::shared_ptr<BlockContext> blockContext, std::shared_ptr<TxContext> txContext)
    : pc(0), contract(contract), value(value), input(input), caller(caller),
      state(state), blockContext(blockContext), txContext(txContext) {
    stack = std::make_unique<Stack>();
    memory = std::make_shared<Memory>();
  }

  uint64_t getPc() { return pc; }
  void setPc(uint64_t pc) { this->pc = pc; }
  void incPc() { pc++; }

  intx::uint256 getValue() { return value; }
  void setValue(intx::uint256 value) { this->value = value; }

  bytes getInput() { return input; }
  uint256 getInputAt(uint64_t index) {
    return input.at(index);
  }
  uint8_t* getInputPtrAt(uint64_t index) {
    return &input.at(index);
  }
  void setInput(bytes input) { this->input = input; }
  uint256 getInputSize() { return input.size(); }

  void setRet(bytes ret) { this->ret = ret; }
  std::string getRetString() {
    std::string result;
    for (const auto &byte : ret) {
      result += toHex(byte);
    }
    return result;
  }

  bytes getReturnData() { return returnData; }
  uint8_t* getReturnDataPtrAt(uint64_t index) {
    return &returnData.at(index);
  }
  uint64_t getReturnDataSize() { return returnData.size(); }
  void setReturnData(bytes returnData) { this->returnData = returnData; }

  uint64_t getBaseFee() { return baseFee; }

  std::shared_ptr<Contract> getContract() { return contract; }
  std::shared_ptr<Stack> getStack() { return stack; } // TODO?
  std::shared_ptr<Memory> getMemory() { return memory; }
  std::shared_ptr<State> getState() { return state; }
  std::shared_ptr<BlockContext> getBlockContext() { return blockContext; }
  std::shared_ptr<TxContext> getTxContext() { return txContext; }

  address getCaller() { return caller; }
  std::string getCallerString() {
    std::string result;
    for (const auto &byte : caller) {
      result += toHex(byte);
    }
    return result;
  }

  bytes run(); // TODO: return value?
  bytes deploy(); // TODO: return value?
  bytes deployAt(address); // TODO: return value?

private:
  uint64_t pc;
  // TODO: are these in the correct context
  intx::uint256 value;
  bytes input;
  bytes ret; // TODO: move to operation?
  bytes returnData;
  uint64_t baseFee;

  std::shared_ptr<Contract> contract;
  address caller; // TODO: In contract?
  std::shared_ptr<Stack> stack; // TODO: shared or unique?
  std::shared_ptr<Memory> memory;
  std::shared_ptr<State> state;

  std::shared_ptr<BlockContext> blockContext;
  std::shared_ptr<TxContext> txContext;


  std::string toHex(uint8_t byte) {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(byte);
    return ss.str();
  }
};
