#include <fstream>
#include <iomanip>

#include "utils.h"

bytes parseBytecode(const std::string& bytecode) {
  bytes result;
  for(int i = 0; i < bytecode.size(); i += 2) {
    std::string byteString = bytecode.substr(i, 2);
    uint8_t byte = std::stoi(byteString, nullptr, 16);
    result.push_back(byte);
  }

  return result;
}

bytes parseBytecodeFile(const std::string& filename) {
  std::ifstream file(filename);
  std::string bytecode;
  std::getline(file, bytecode);
  // TODO: handle errors & multiple lines
  return parseBytecode(bytecode);
}

std::string byteToHex(uint8_t byte) {
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(byte);
  return ss.str();
}

std::string bytecodeToHex(const bytes& bytecode) {
  std::stringstream ss;
  for(uint8_t byte : bytecode) {
    ss << byteToHex(byte);
  }
  return ss.str();
}

bytes compileContract(const std::string& source) {
  // TODO: implement
  return bytes();
}
