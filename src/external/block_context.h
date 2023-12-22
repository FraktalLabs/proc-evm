#pragma once

#include <iomanip>
#include <sstream>

#include <intx/intx.hpp>

#include "../utils/types.h"

class BlockContext {
public:
  BlockContext(): coinbase(), gasLimit(0), timestamp(0), number(0), difficulty(0), chainId(0) {};
  BlockContext(address coinbase, uint64_t gasLimit, uint64_t timestamp,
               intx::uint256 number, intx::uint256 difficulty)
      : coinbase(coinbase), gasLimit(gasLimit), timestamp(timestamp),
        number(number), difficulty(difficulty) {}
  BlockContext(const std::string& blockContextFile) {
    // TODO
  }

  address getCoinbase() const { return coinbase; }
  std::string getCoinbaseString() const {
    std::string result;
    for (const auto &byte : coinbase) {
      result += toHex(byte);
    }
    return result;
  }

  uint64_t getGasLimit() const { return gasLimit; }
  uint64_t getTimestamp() const { return timestamp; }
  intx::uint256 getNumber() const { return number; }
  intx::uint256 getDifficulty() const { return difficulty; }
  uint64_t getChainId() const { return chainId; }

  intx::uint256 getBlockHash() {
    // TODO
    return intx::uint256(42);
  }

private:
  address coinbase;
  uint64_t gasLimit;
  uint64_t timestamp;
  intx::uint256 number;
  intx::uint256 difficulty;
  uint64_t chainId;

  std::string toHex(uint8_t byte) const {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(byte);
    return ss.str();
  }
};
