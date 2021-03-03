#include "PeParser.h"
#include "ImageDosHeader.h"
#include "ImageSectionHeader.h"
#include "OptionalHeaderMagicValues.h"

namespace exe_inject {

auto PeParser::Parse(const std::filesystem::path& path) const -> std::pair<ImageNtHeaders, Sections> {
  auto file = std::fstream{ path.string(), std::ios::binary | std::ios::in };

  if (!file.is_open()) {
    throw std::runtime_error{ "Open file error" };
  }

  std::stringstream pe_data;

  std::copy(
    std::istreambuf_iterator<char>(file),
    std::istreambuf_iterator<char>(),
    std::ostreambuf_iterator<char>(pe_data)
  );

  const auto binary_payload = pe_data.str();

  ImageDosHeader image_dos_header{};
  memcpy(&image_dos_header, binary_payload.data(), sizeof(ImageDosHeader));

  ImageNtHeaders image_nt_headers{};

  const auto signature_offset = binary_payload.data() + image_dos_header.e_lfanew;
  const auto file_header_offset = signature_offset + sizeof(image_nt_headers.signature);
  const auto optional_header_offset = file_header_offset + sizeof(image_nt_headers.image_file_header);

  memcpy(&image_nt_headers.signature, signature_offset, sizeof(image_nt_headers.signature));
  memcpy(&image_nt_headers.image_file_header, file_header_offset, sizeof(image_nt_headers.image_file_header));

  if (image_nt_headers.image_file_header.size_of_optional_header) {
    uint16_t magic;
    memcpy(&magic, optional_header_offset, sizeof(magic));

    switch (magic) {
      case kImageNtOptionalHdr32Magic: {
        ImageOptionalHeader32 optional_header{};
        memcpy(&optional_header, optional_header_offset, sizeof(optional_header));
        image_nt_headers.image_optional_header = optional_header;
        break;
      }
      case kImageNtOptionalHdr64Magic: {
        ImageOptionalHeader64 optional_header{};
        memcpy(&optional_header, optional_header_offset, sizeof(optional_header));
        image_nt_headers.image_optional_header = optional_header;
        break;
      }
      default: {
        throw std::runtime_error{ "Unsupported PE magic value " + std::to_string(magic) };
      }
    }
  }

  auto section_offset = optional_header_offset + image_nt_headers.image_file_header.size_of_optional_header;

  std::vector<ImageSectionHeader> sections;

  for (auto i{ 0 }; i < image_nt_headers.image_file_header.number_of_sections; ++i) {
    ImageSectionHeader section_header;
    memcpy(&section_header, section_offset, sizeof(ImageSectionHeader));
    sections.push_back(section_header);
    section_offset += sizeof(ImageSectionHeader);
  }

  return { image_nt_headers, sections };
}

} // namespace exe_inject
