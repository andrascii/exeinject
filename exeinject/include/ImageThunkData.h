#pragma once

namespace exe_inject {

struct alignas(8) ImageThunkData64 {
  union {
    uint64_t forwarder_string;
    uint64_t function;
    uint64_t ordinal;
    uint64_t address_of_data;
  } u1;
};

struct ImageThunkData32 {
  union {
    uint32_t forwarder_string;
    uint32_t function;
    uint32_t ordinal;
    uint32_t address_of_data;
  } u1;
};

using ImageThunkData = std::variant<ImageThunkData32, ImageThunkData64>;

}
