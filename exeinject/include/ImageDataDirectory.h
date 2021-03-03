#pragma once

namespace exe_inject {

constexpr auto kImageNumberOfDirectoryEntries = 16;

struct ImageDataDirectory {
  std::uint32_t virtual_address;
  std::uint32_t size;
};

}
