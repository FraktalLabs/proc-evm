#pragma once

#include <array>
#include <cstdint>
#include <iomanip>
#include <sstream>

#include <intx/intx.hpp>

using address = std::array<uint8_t, 20>;

class TxContext {
public:
  TxContext(): origin(), gasPrice() {}
  TxContext(address origin, intx::uint256 gasPrice)
      : origin(origin), gasPrice(gasPrice) {}

  address getOrigin() const { return origin; }
  std::string getOriginString() {
    std::string result;
    for (const auto &byte : origin) {
      result += toHex(byte);
    }
    return result;
  }

  intx::uint256 getGasPrice() const { return gasPrice; }
private:
  address origin;
  intx::uint256 gasPrice;

  std::string toHex(uint8_t byte) {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(byte);
    return ss.str();
  }
};
