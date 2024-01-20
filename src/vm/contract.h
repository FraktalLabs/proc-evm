#pragma once

#include <sstream>
#include <iomanip>

#include "opcodes.h"

#include <evm-cpp-utils/utils.h>

// TODO: Think about using Enum for bytecodes and compress into uint8_t somehow for DA

class Contract {
public:
  Contract(bytes bytecode) : bytecode(bytecode) {}
  Contract(bytes bytecode, const std::string& address) : bytecode(bytecode) { setAddress(address); }
  // Contract(std::string bytecode) : bytecode(bytecode.begin(), bytecode.end()) {}

  const bytes& getBytecode() const { return bytecode; }
  uint8_t getBytecodeAt(uint64_t index) const { return bytecode[index]; }
  uint8_t* getBytecodePtrAt(uint64_t index) { return &bytecode[index]; }
  uint64_t getBytecodeSize() const { return bytecode.size(); }
  Opcode getOpcodeAt(uint64_t index) const { return static_cast<Opcode>(bytecode[index]); }
  ExtensionOpcode getExtensionOpcodeAt(uint64_t index) const { return static_cast<ExtensionOpcode>(bytecode[index]); }

  std::string getBytecodeString(bool spaced = false) {
    std::string result;
    for (const auto &byte : bytecode) {
      result += byteToHex(byte) + (spaced ? " " : "");
    }
    return result;
  }

  std::string getBytecodeStringAt(uint64_t index) {
    return byteToHex(bytecode[index]);
  }

  uint64_t getCodeSize() const {
    return bytecode.size();
  }

  address getAddress() const {
    return address;
  }

  std::string getAddressString() {
    std::string result;
    for (const auto &byte : address) {
      result += byteToHex(byte);
    }
    return result;
  }

  void setAddress(address address) {
    this->address = address;
  }

  void setAddress(const std::string& address) {
    for (int i = 0; i < 20; i++) {
      this->address[i] = std::stoi(address.substr(i * 2, 2), nullptr, 16);
    }
  }

private:
  // TODO: bytes_view? pointer?
  bytes bytecode;
  address address;
};
