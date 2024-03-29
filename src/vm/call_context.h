#pragma once

#include <memory>

#include "contract.h"
#include "memory.h"
#include "stack.h"

#include <iostream>
#include <string>

#include <evm-cpp-utils/types.h>

class CallContext {
public:
  CallContext(std::shared_ptr<Contract> contract, uint64_t pc)
      : pc(pc), value(0), input(), contract(contract), caller() {
    stack = std::make_unique<Stack>();
    memory = std::make_shared<Memory>();
    state = std::make_shared<State>();
    blockContext = std::make_shared<BlockContext>();
    txContext = std::make_shared<TxContext>();
  }
  CallContext(std::shared_ptr<Contract> contract, uint64_t pc, std::shared_ptr<State> state)
      : pc(pc), value(0), input(), contract(contract), caller(), state(state) {
    stack = std::make_unique<Stack>();
    memory = std::make_shared<Memory>();
    blockContext = std::make_shared<BlockContext>();
    txContext = std::make_shared<TxContext>();
  }
  CallContext(std::shared_ptr<Contract> contract, uint64_t pc, std::shared_ptr<State> state,const std::string& callAddress)
      : pc(pc), value(0), input(), contract(contract), caller(), state(state) {
    contract->setAddress(callAddress);
    stack = std::make_unique<Stack>();
    memory = std::make_shared<Memory>();
    blockContext = std::make_shared<BlockContext>();
    txContext = std::make_shared<TxContext>();
  }
  CallContext(std::shared_ptr<Contract> contract, intx::uint256 value, bytes input, address caller,
              std::shared_ptr<State> state, std::shared_ptr<BlockContext> blockContext, std::shared_ptr<TxContext> txContext)
    : pc(0), value(value), input(input), contract(contract), caller(caller),
      state(state), blockContext(blockContext), txContext(txContext) {
    stack = std::make_unique<Stack>();
    memory = std::make_shared<Memory>();
  }

  virtual ~CallContext() {}

  uint64_t getPc() const { return pc; }
  void setPc(uint64_t pc) { this->pc = pc; }
  void incPc() { pc++; }

  intx::uint256 getValue() const { return value; }
  void setValue(intx::uint256 value) { this->value = value; }

  bytes getInput() const { return input; }
  uint256 getInputAt(uint64_t index) const {
    if (index > input.size()) {
      return 0;
    }

    bytes in;
    in.resize(32);
    for(int i = 0; i < 32 && index + i < input.size(); i++) {
      in[i] = input[index + i];
    }
    return intx::be::unsafe::load<uint256>(in.data());
  }
  uint8_t* getInputPtrAt(uint64_t index) {
    return &input.at(index);
  }
  void setInput(bytes input) { this->input = input; }
  uint256 getInputSize() const { return input.size(); }

  void setRet(bytes ret) { this->ret = ret; }
  std::string getRetString() const {
    std::string result;
    for (const auto &byte : ret) {
      result += toHex(byte);
    }
    return result;
  }

  bytes getReturnData() const { return returnData; }
  uint8_t* getReturnDataPtrAt(uint64_t index) {
    return &returnData.at(index);
  }
  uint64_t getReturnDataSize() const { return returnData.size(); }
  void setReturnData(bytes returnData) { this->returnData = returnData; }

  uint64_t getBaseFee() const { return baseFee; }

  std::shared_ptr<Contract> getContract() { return contract; }
  std::shared_ptr<Stack> getStack() { return stack; }
  void setStack(std::shared_ptr<Stack> stack) { this->stack = stack; }
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

  virtual bytes run();
  bytes deploy();
  bytes deployAt(address);

private:
  uint64_t pc;
  intx::uint256 value;
  bytes input;
  bytes ret; // TODO: move to operation?
  bytes returnData;
  uint64_t baseFee;

  std::shared_ptr<Contract> contract;
  address caller;
  std::shared_ptr<Stack> stack;
  std::shared_ptr<Memory> memory;
  std::shared_ptr<State> state;

  std::shared_ptr<BlockContext> blockContext;
  std::shared_ptr<TxContext> txContext;


  std::string toHex(uint8_t byte) const {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(byte);
    return ss.str();
  }
};
