#include "PeParser.h"
#include "ImageDosHeader.h"
#include "ImageSectionHeader.h"
#include "OptionalHeaderMagicValues.h"
#include "ImageImportDescriptor.h"
#include "ImageThunkData.h"

namespace exe_inject {

auto PeParser::Parse(const std::filesystem::path& path) const -> Info {
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

  auto is_pe32_plus{ false };

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
        is_pe32_plus = true;
        break;
      }
      default: {
        throw std::runtime_error{ "Unsupported PE magic value " + std::to_string(magic) };
      }
    }
  }

  const auto import_directory_rva = ImportDirectoryRva(image_nt_headers.image_optional_header);
  auto section_offset = optional_header_offset + image_nt_headers.image_file_header.size_of_optional_header;

  ImportInfo import_info;
  std::vector<ImageSectionHeader> sections;

  for (auto i{ 0 }; i < image_nt_headers.image_file_header.number_of_sections; ++i) {
    ImageSectionHeader section_header;
    memcpy(&section_header, section_offset, sizeof(ImageSectionHeader));

    const auto is_import_section =
      import_directory_rva >= section_header.virtual_address &&
      import_directory_rva < section_header.virtual_address + section_header.misc.virtual_size;

    if (is_import_section) {
      import_info = FetchImportInfo(import_directory_rva, binary_payload.data(), section_header);
    }

    sections.push_back(section_header);
    section_offset += sizeof(ImageSectionHeader);
  }

  return Info{
    image_nt_headers,
    sections,
    import_info
  };
}

auto PeParser::ImportDirectoryRva(const ImageOptionalHeader& optional_header) noexcept -> uint32_t {
  return std::visit([](const auto& header) {
    return header.data_directory[kImageDirectoryEntryImport].virtual_address;
  }, optional_header);
}

auto PeParser::FetchImportInfo(
  uint32_t import_directory_rva,
  const char* payload,
  const ImageSectionHeader& import_section
) noexcept -> ImportInfo {
  ImportInfo import_info;

  const auto import_offset = payload + import_section.pointer_to_raw_data;
  const auto import_descriptor_offset = import_offset + import_directory_rva - import_section.virtual_address;
  const auto* import_descriptor = reinterpret_cast<const ImageImportDescriptor*>(import_descriptor_offset);

  for (; import_descriptor->name; ++import_descriptor) {
    const auto thunk =
      import_descriptor->original_first_thunk == 0 ?
      import_descriptor->first_thunk :
      import_descriptor->original_first_thunk;

    const auto* thunk_data = reinterpret_cast<const ImageThunkData64*>(import_offset + thunk - import_section.virtual_address);
    const auto module_name = std::string{ import_offset + import_descriptor->name - import_section.virtual_address };

    for (; thunk_data->u1.address_of_data != 0; ++thunk_data) {
      import_info[module_name].push_back(import_offset + thunk_data->u1.address_of_data - import_section.virtual_address + 2);
    }
  }

  return import_info;
}

} // namespace exe_inject
