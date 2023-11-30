#include <cstring>

#include "memory.h"
#include <iostream>

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

void Memory::store32(uint64_t offset, uint32_t value) {
  //TODO: Move? Check sizing / offsets?
  //   when does go version resize
  if (offset + 4 > size) {
    resize(offset + 4);
  }

  // TODO: Endian?
  memory[offset] = value & 0xFF;
  memory[offset + 1] = (value >> 8) & 0xFF;
  memory[offset + 2] = (value >> 16) & 0xFF;
  memory[offset + 3] = (value >> 24) & 0xFF;
}

uint32_t Memory::load32(uint64_t offset) {
  uint8_t* ptr = &memory[offset];
  uint32_t value = ptr[0] | (ptr[1] << 8) | (ptr[2] << 16) | (ptr[3] << 24);
  return value;
}
