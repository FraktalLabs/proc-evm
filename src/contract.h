#pragma once

#include <string>
#include <sstream>
#include <iomanip>
#include <array>

#include "opcodes.h"

using bytes = std::basic_string<uint8_t>;
using address = std::array<uint8_t, 20>;

// TODO: Think about using Enum for bytecodes and compress into uint8_t somehow for DA

class Contract {
public:
  Contract(bytes bytecode) : bytecode(bytecode) {}
  // Contract(std::string bytecode) : bytecode(bytecode.begin(), bytecode.end()) {}

  const bytes& getBytecode() const { return bytecode; }
  uint8_t getBytecodeAt(uint64_t index) const { return bytecode[index]; }
  uint64_t getBytecodeSize() const { return bytecode.size(); }
  Opcode getOpcodeAt(uint64_t index) const { return static_cast<Opcode>(bytecode[index]); }

  std::string getBytecodeString(bool spaced = false) {
    std::string result;
    for (const auto &byte : bytecode) {
      result += toHex(byte) + (spaced ? " " : "");
    }
    return result;
  }

  std::string getBytecodeStringAt(uint64_t index) {
    return toHex(bytecode[index]);
  }

  std::string getAddressString() {
    std::string result;
    for (const auto &byte : address) {
      result += toHex(byte);
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

  std::string toHex(uint8_t byte) {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(byte);
    return ss.str();
  }

};
