#pragma once

#include <array>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include <intx/intx.hpp>

using bytes = std::basic_string<uint8_t>;
using address = std::array<uint8_t, 20>;

class TxContext {
public:
  TxContext(): origin(), gasPrice() {}
  TxContext(address origin, intx::uint256 gasPrice)
      : origin(origin), gasPrice(gasPrice) {}
  TxContext(const std::string& txContextFile) {
    // TODO
  }

  address getOrigin() const { return origin; }
  std::string getOriginString() {
    std::string result;
    for (const auto &byte : origin) {
      result += toHex(byte);
    }
    return result;
  }

  intx::uint256 getGasPrice() const { return gasPrice; }

  bytes getBlobHash(uint64_t index) const { return blobHashes[index]; }
  std::string getBlobHashString(uint64_t index) const {
    std::string result;
    for (const auto &byte : blobHashes[index]) {
      result += toHex(byte);
    }
    return result;
  }
private:
  address origin;
  intx::uint256 gasPrice;
  // TODO: Not sure on this type
  std::vector<bytes> blobHashes;

  std::string toHex(uint8_t byte) const {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(byte);
    return ss.str();
  }
};
