#include "memory.h"

#include <cstring>

Memory::Memory() {
  size = 0;
  capacity = DEFAULT_CAPACITY;
  memory = new uint8_t[capacity];
}

Memory::~Memory() {
  delete[] memory;
}

uint64_t Memory::getSize() {
  return size;
}

uint64_t Memory::getCapacity() {
  return capacity;
}

uint8_t* Memory::getMemory() {
  return memory;
}

void Memory::resize(uint64_t newSize) {
  if (newSize > capacity) {
    capacity *= CAPACITY_MULTIPLIER;
    if (newSize > capacity) {
      capacity = (newSize / DEFAULT_CAPACITY + 1) * DEFAULT_CAPACITY;
    }

    // TODO: use realloc? other efficient way?
    uint8_t* newMemory = new uint8_t[capacity];
    for (uint64_t i = 0; i < size; i++) {
      newMemory[i] = memory[i];
    }

    delete[] memory;
    memory = newMemory;
  }
  size = newSize;
}

void Memory::clear() {
  size = 0;
}

uint8_t& Memory::operator[](uint64_t index) {
  return memory[index];
}

std::string Memory::toString() {
  static uint16_t rowSize = 16;
  std::string result = "";
  for (uint64_t i = 0; i < size; i++) {
    if (i % rowSize == 0 && i != 0) {
      result += "\n";
    }
    result += std::to_string(memory[i]) + " ";
  }
  return result;
}

void Memory::store32(uint64_t offset, const intx::uint256& value) {
  //TODO: Move? Check sizing / offsets?
  // TODO: double on resize? or just add 32?
  //   when does go version resize
  if (offset + 32 > size) {
    resize(offset + 32);
  }

  intx::be::unsafe::store(&memory[offset], value);
  // TODO: Endian?
}

void Memory::store(uint64_t offset, uint64_t length, uint8_t* data) {
  if (offset + length > size) {
    resize(offset + length);
  }

  for (uint64_t i = 0; i < length; i++) {
    memory[offset + i] = data[i];
  }
}

void Memory::copy(uint64_t dest, uint64_t src, uint64_t length) {
  if (dest + length > size) {
    resize(dest + length);
  }

  for (uint64_t i = 0; i < length; i++) {
    memory[dest + i] = memory[src + i];
  }
}

intx::uint256 Memory::load32(uint64_t offset) {
  // TODO: check sizing / offsets & do padding
  return intx::be::unsafe::load<intx::uint256>(&memory[offset]);
}

uint8_t* Memory::getPointer(uint64_t offset) {
  return &memory[offset];
}
