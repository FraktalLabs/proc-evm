#include "rlp.h"

template <uint8_t SHORTBASE, uint8_t LONGBASE>
bytes encode_length(size_t length) {
  static constexpr uint8_t SHORT_CUTOFF = 55;

  if (length <= SHORT_CUTOFF) {
    return {static_cast<uint8_t>(length + SHORTBASE)};
  } else if (const auto l0 = static_cast<uint8_t>(length); length <= 0xff) {
    return {LONGBASE + 1, l0};
  } else if (const auto l1 = static_cast<uint8_t>(length >> 8); length <= 0xffff) {
    return {LONGBASE + 2, l1, l0};
  } else {
    return {LONGBASE + 3, static_cast<uint8_t>(length >> 16), l1, l0};
  }
}

bytes encode(bytes_view data) {
  static constexpr uint8_t SHORT_BASE = 128;
  if (data.size() == 1 && data[0] < SHORT_BASE) {
    return {data[0]};
  }
  return encode_length<SHORT_BASE, 183>(data.size()) += data;
}

bytes_view trim(bytes_view data) {
  data.remove_prefix(std::min(data.find_first_not_of(uint8_t{0}), data.size()));
  return data;
}

bytes encode(uint64_t data) {
  uint8_t buf[sizeof(data)];
  intx::be::store(buf, data);
  return encode(trim({buf, sizeof(buf)}));
}

bytes wrap_list(const bytes& data) {
  return encode_length<192, 247>(data.size()) + data;
}

template <typename InputIterator>
bytes encode_container(InputIterator first, InputIterator last) {
  bytes result;
  for (; first != last; ++first) {
    result += encode(*first);
  }
  return wrap_list(result);
}

template <typename T, size_t N>
bytes encode(const T (&data)[N]) {
  return encode_container(std::begin(data), std::end(data));
}
