#pragma once

#include "account.h"

#include <array>

//using address = uint8_t[20];
using address = std::array<uint8_t, 20>;

class State {
public:
  State() {}
  State(const std::string& snapshot) {
    restore(snapshot);
  }

  void snapshot(const std::string& filepath);
  void restore(const std::string& filepath);

  void insert(const address& addr, const Account& account) {
    state[addr] = account;
  }

  void insert(const std::string& addr, const Account& account) {
    uint8_t keyBytes[20];
    for (int i = 0; i < 20; i++) {
      std::string byteStr = addr.substr(i * 2, 2);
      keyBytes[i] = static_cast<uint8_t>(std::stoi(byteStr, nullptr, 16));
    }
    std::array<uint8_t, 20> keyArray;
    std::copy(keyBytes, keyBytes + 20, keyArray.begin());
    insert(keyArray, account);
  }

  Account* getAccount(const address& addr) {
    auto it = state.find(addr);
    if (it == state.end()) {
      return nullptr;
    }
    return &it->second;
  }
  Account* getAccount(const std::string& addr) {
    uint8_t keyBytes[20];
    for (int i = 0; i < 20; i++) {
      std::string byteStr = addr.substr(i * 2, 2);
      keyBytes[i] = static_cast<uint8_t>(std::stoi(byteStr, nullptr, 16));
    }
    std::array<uint8_t, 20> keyArray;
    std::copy(keyBytes, keyBytes + 20, keyArray.begin());
    return getAccount(keyArray);
  }
  void removeAccount(const address& addr) {
    state.erase(addr);
  }
  void removeAccount(const std::string& addr) {
    uint8_t keyBytes[20];
    for (int i = 0; i < 20; i++) {
      std::string byteStr = addr.substr(i * 2, 2);
      keyBytes[i] = static_cast<uint8_t>(std::stoi(byteStr, nullptr, 16));
    }
    std::array<uint8_t, 20> keyArray;
    std::copy(keyBytes, keyBytes + 20, keyArray.begin());
    removeAccount(keyArray);
  }

private:
  std::map<address, Account> state;
};
