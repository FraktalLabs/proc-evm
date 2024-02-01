#pragma once

#include <cstdint>
#include <string>

#include <evm-cpp-utils/types.h>

class Memory {
public:
  Memory();
  ~Memory();

  uint64_t getSize();
  uint64_t getCapacity();
  uint8_t* getMemory();

  void resize(uint64_t newSize);
  void clear();

  uint8_t& operator[](uint64_t index);
  void store32(uint64_t, const intx::uint256&);
  void store(uint64_t, uint64_t, uint8_t*);
  void copy(uint64_t, uint64_t, uint64_t);
  intx::uint256 load32(uint64_t);
  uint8_t* getPointer(uint64_t);

  std::string toString();
private:
  uint8_t* memory;
  uint64_t size;
  uint64_t capacity;

  static const uint64_t DEFAULT_CAPACITY = 4*1024;
  static const uint64_t CAPACITY_MULTIPLIER = 2;
};
