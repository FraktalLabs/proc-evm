#pragma once

#include <cstdint>
#include <string>
#include <array>

using bytes = std::basic_string<uint8_t>;
using bytes_view = std::basic_string_view<uint8_t>;
using address = std::array<uint8_t, 20>;
