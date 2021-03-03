#pragma once

#include "ImageNtHeaders.h"
#include "ImageSectionHeader.h"

namespace exe_inject {

class PeParser final {
public:
  auto Parse(const std::filesystem::path& path) const -> std::pair<ImageNtHeaders, Sections>;
};

} // namespace exe_inject
