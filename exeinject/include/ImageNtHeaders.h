#pragma once

#include "ImageFileHeader.h"
#include "VariantVisitor.h"
#include "ImageOptionalHeader32.h"
#include "ImageOptionalHeader64.h"

namespace exe_inject {

using ImageOptionalHeader = std::variant<ImageOptionalHeader32, ImageOptionalHeader64>;

template <typename C>
auto TakeOptionalHeaderInfo(const ImageOptionalHeader& optional_header, C&& functor) {
  VariantVisitor visitor{
    [&](const ImageOptionalHeader32& header) { return functor(header); },
    [&](const ImageOptionalHeader64& header) { return functor(header); },
  };

  return std::visit(visitor, optional_header);
}

struct ImageNtHeaders {
  std::uint32_t signature;
  ImageFileHeader image_file_header;
  ImageOptionalHeader image_optional_header;
};

}
