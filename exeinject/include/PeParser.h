#pragma once

#include "ImageNtHeaders.h"
#include "ImageSectionHeader.h"

namespace exe_inject {

class PeParser final {
public:
  using ModuleName = std::string;
  using ExportFunctionNames = std::vector<std::string>;
  using ImportInfo = std::map<ModuleName, ExportFunctionNames>;

  struct Info {
    ImageNtHeaders nt_headers;
    Sections sections;
    ImportInfo import_info;
  };

  auto Parse(const std::filesystem::path& path) const -> Info;

private:
  static auto ImportDirectoryRva(const ImageOptionalHeader& optional_header) noexcept -> uint32_t;

  static auto FetchImportInfo(
    uint32_t import_directory_rva,
    const char* payload,
    const ImageSectionHeader& import_section
  ) noexcept -> ImportInfo;
};

} // namespace exe_inject
