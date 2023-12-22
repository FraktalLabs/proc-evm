#pragma once

#include <string>

#include <intx/intx.hpp>

using bytes = std::basic_string<uint8_t>;
using bytes_view = std::basic_string_view<uint8_t>;

template <uint8_t SHORTBASE, uint8_t LONGBASE>
bytes encode_length(size_t length);

bytes encode(bytes_view data);
bytes_view trim(bytes_view data);
bytes encode(uint64_t data);
bytes wrap_list(const bytes& data);

template <typename... Types>
bytes encode_tuple(const Types&... args) {
  return wrap_list((encode(args) + ...));
}


template <typename InputIterator>
bytes encode_container(InputIterator first, InputIterator last);

template <typename T, size_t N>
bytes encode(const T (&data)[N]);
