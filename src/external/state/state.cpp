#include "state.h"

#include <fstream>
#include <string>
#include <array>

std::string toHex(uint8_t byte) {
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(byte);
  return ss.str();
}

void State::snapshot(const std::string& filepath) {
// For now : Use pretty-json like formatting
  std::string serialized = "[\n";
  for (auto it = state.begin(); it != state.end(); ++it) {
    serialized += "  {\n";
    serialized += "    \"";
    for (const auto &byte : it->first) {
      serialized += toHex(byte);
    }
    serialized += "\" : " + it->second.toSerialized();
    if (it == --state.end()) {
      serialized += "\n  }\n";
    } else {
      serialized += "\n  },\n";
    }
  }
  serialized += "]\n";

  // Open file for writing
  std::ofstream file(filepath);
  file << serialized;
  file.close();

}

void State::restore(const std::string& filepath) {
  // Open file for reading
  std::ifstream file(filepath);
  std::string line;

  // Flatten json file
  std::string flattened;
  while (std::getline(file, line)) {
    // trim line
    line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
    flattened += line;
  }
  file.close();

  // Parse flattened json
  // [ { "address": { value } }, { "address": { value } } ]
  
  // Loop through { "address": { value } } items
  std::string item;
  bool isItem = false;
  uint64_t bracketCount = 0;
  for (const auto &c : flattened) {
    if (c == '{') {
      isItem = true;
      bracketCount++;
      if (bracketCount != 1) {
        item += c;
      }
    } else if (c == '}') {
      bracketCount--;
      if (bracketCount == 0) {
        isItem = false;

        std::string key;
        std::string value;
        bool isKey = false;
        bool isValue = false;
        bool valueColon = false;
        for (const auto &c : item) {
          if (c == '"' && !isValue) {
            if (isKey) {
              isKey = false;
              isValue = true;
              valueColon = true;
            } else {
              isKey = true;
            }
          } else if (c == ':' && !isValue) {
            continue;
          } else if (c == ':' && valueColon) {
            valueColon = false;
            continue;
          } else if (isKey) {
            key += c;
          } else if (isValue) {
            value += c;
          }
        }
        uint8_t keyBytes[20];
        for (int i = 0; i < 20; i++) {
          std::string byteStr = key.substr(i * 2, 2);
          keyBytes[i] = static_cast<uint8_t>(std::stoi(byteStr, nullptr, 16));
        }
        std::array<uint8_t, 20> keyArray;
        std::copy(keyBytes, keyBytes + 20, keyArray.begin());
        insert(keyArray, Account(value));
        //state[keyBytes] = Account(value);

        item = "";
      } else {
        item += c;
      }
    } else if (isItem) {
      item += c;
    }
  }
}
