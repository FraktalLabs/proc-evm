#pragma once

#include <string>

using bytes = std::basic_string<uint8_t>;

bytes parseBytecode(const std::string& bytecode);
bytes parseBytecodeFile(const std::string& filename);
std::string byteToHex(uint8_t byte);
std::string bytecodeToHex(const bytes& bytecode);

bytes compileContract(const std::string& source);
