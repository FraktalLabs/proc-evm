#pragma once

#include <string>
#include <map>
#include <sstream>
#include <iomanip>
#include <iostream>

#include <intx/intx.hpp>

using bytes = std::basic_string<uint8_t>;

class Account {
public:
  Account() : nonce(0), balance(0) {}
  Account(const std::string& serialized): nonce(0), balance(0) {
    std::cout << "Account serialized: " << serialized << std::endl;
    // Parse the flattened json like
    // {"nonce"123,"balance"3001,"storage"[],"code""6020600052"}
    for (size_t i = 0; i < serialized.size(); ++i) {
      if (serialized[i] == '{') {
        continue;
      } else if (serialized[i] == '"') {
        // Parse key
        std::string key;
        for (++i; serialized[i] != '"'; ++i) {
          key += serialized[i];
        }
        ++i; // Skip the closing "
        ++i; // Skip the :
        if (key == "nonce") {
          // Parse nonce
          std::string nonceStr;
          for (; serialized[i] != ','; ++i) {
            nonceStr += serialized[i];
          }
          nonce = std::stoull(nonceStr);
          std::cout << "nonce: " << nonce << std::endl;
        } else if (key == "balance") {
          // Parse balance
          std::string balanceStr;
          for (; serialized[i] != ','; ++i) {
            balanceStr += serialized[i];
          }
          balance = intx::from_string<intx::uint256>(balanceStr);
          std::cout << "balance: " << to_string(balance) << std::endl;
        } else if (key == "storage") {
          // Parse storage
          for (; serialized[i] != '['; ++i) {}
          for (++i; serialized[i] != ']'; ++i) {
            // Parse key
            std::string keyStr;
            for (++i; serialized[i] != '"'; ++i) {
              keyStr += serialized[i];
            }
            ++i; // Skip the closing "
            ++i; // Skip the :
            // Parse value
            std::string valueStr;
            for (; serialized[i] != ',' && serialized[i] != ']'; ++i) {
              valueStr += serialized[i];
            }
            storage[intx::from_string<intx::uint256>(keyStr)] = intx::from_string<intx::uint256>(valueStr);
            std::cout << "storage[" << keyStr << "] = " << valueStr << std::endl;
            if (serialized[i] == ']') {
              break;
            }
          }
          std::cout << "storage size: " << storage.size() << std::endl;
        } else if (key == "code") {
          // Parse code
          ++i; // Skip the opening "
          for (; serialized[i] != '"'; ++i) {
            code.push_back(fromHex(serialized.substr(i, 2)));
            ++i;
          }
          std::cout << "code size: " << code.size() << std::endl;
        }
      }
    }
  }

  std::string toString() const {
    return "Account{nonce=" + std::to_string(nonce) + ", balance=" + to_string(balance) + ", storage=" + std::to_string(storage.size()) + ", code=" + std::to_string(code.size()) + "}";
  }

  std::string toSerialized() const {
    // For now : Use pretty-json like formatting
    std::string serialized = "{\n";
    serialized += "      \"nonce\": " + std::to_string(nonce) + ",\n";
    serialized += "      \"balance\": " + to_string(balance) + ",\n";
    serialized += "      \"storage\": [\n";
    for (auto it = storage.begin(); it != storage.end(); ++it) {
      serialized += "        \"" + to_string(it->first) + "\": " + to_string(it->second) + "";
      if (std::next(it) != storage.end()) {
        serialized += ",";
      }
      serialized += "\n";
    }
    serialized += "      ],\n";
    serialized += "      \"code\": \"";
    for (const auto &byte : code) {
      serialized += toHex(byte);
    }
    serialized += "\"\n";
    serialized += "    }";
    return serialized;
  }

  uint64_t getNonce() const {
    return nonce;
  }

  intx::uint256 getBalance() const {
    return balance;
  }

  intx::uint256 getStorage(const intx::uint256& key) const {
    auto it = storage.find(key);
    if (it != storage.end()) {
      return it->second;
    }
    return 0;
  }

  void setStorage(const intx::uint256& key, const intx::uint256& value) {
    storage[key] = value;
  }

private:
  uint64_t nonce;
  intx::uint256 balance;
  std::map<intx::uint256, intx::uint256> storage; // Maps storage key to storage value TODO: use other data structure
  bytes code;

  std::string toHex(uint8_t byte) const {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(byte);
    return ss.str();
  }

  uint8_t fromHex(const std::string& hex) {
    uint8_t byte = (uint8_t) strtol(hex.c_str(), nullptr, 16);;
    //std::stringstream ss;
    //ss << std::hex << hex;
    //ss >> byte;
    return byte;
  }

};
