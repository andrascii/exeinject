#pragma once

#include "ImageDataDirectory.h"

namespace exe_inject {

struct ImageOptionalHeader32 {
  //
  // Standard fields.
  //

  uint16_t magic;
  uint8_t major_linker_version;
  uint8_t minor_linker_version;
  uint32_t size_of_code;
  uint32_t size_of_initialized_data;
  uint32_t size_of_uninitialized_data;
  uint32_t address_of_entry_point;
  uint32_t base_of_code;
  uint32_t base_of_data;

  //
  // NT additional fields.
  //

  uint32_t image_base;
  uint32_t section_alignment;
  uint32_t file_alignment;
  uint16_t major_operating_system_version;
  uint16_t minor_operating_system_version;
  uint16_t major_image_version;
  uint16_t minor_image_version;
  uint16_t major_subsystem_version;
  uint16_t minor_subsystem_version;
  uint32_t win32_version_value;
  uint32_t size_of_image;
  uint32_t size_of_headers;
  uint32_t check_sum;
  uint16_t subsystem;
  uint16_t dll_characteristics;
  uint32_t size_of_stack_reserve;
  uint32_t size_of_stack_commit;
  uint32_t size_of_heap_reserve;
  uint32_t size_of_heap_commit;
  uint32_t loader_flags;
  uint32_t number_of_rva_and_sizes;
  ImageDataDirectory data_directory[kImageNumberOfDirectoryEntries];
};

inline auto operator<<(std::ostream& out, const ImageOptionalHeader32& header) noexcept -> std::ostream& {
  out
    << "Magic: " << header.magic << std::endl
    << "Major Linker Version: " << header.major_linker_version << std::endl
    << "Minor Linker Version: " << header.minor_linker_version << std::endl
    << "Size of Code: " << header.size_of_code << std::endl
    << "Size of Initialized Data: " << header.size_of_initialized_data << std::endl
    << "Size of Uninitialized Data: " << header.size_of_uninitialized_data << std::endl
    << "Address of Entry Point: " << header.address_of_entry_point << std::endl
    << "Base of Code: " << header.base_of_code << std::endl
    << "Base of Data: " << header.base_of_data << std::endl
    << "Image Base: " << header.image_base << std::endl
    << "Section Alignment: " << header.section_alignment << std::endl
    << "File Alignment: " << header.file_alignment << std::endl
    << "Major OS Version: " << header.major_operating_system_version << std::endl
    << "Minor OS Version: " << header.minor_operating_system_version << std::endl
    << "Major Image Version: " << header.major_image_version << std::endl
    << "Minor Image Version: " << header.minor_image_version << std::endl
    << "Major Subsystem Version: " << header.major_subsystem_version << std::endl
    << "Minor Subsystem Version: " << header.minor_subsystem_version << std::endl
    << "Win32 Version Value: " << header.win32_version_value << std::endl
    << "Size of Image: " << header.size_of_image << std::endl
    << "Size of Headers: " << header.size_of_headers << std::endl
    << "Check Sum: " << header.check_sum << std::endl
    << "Subsystem: " << header.subsystem << std::endl
    << "Dll Characteristics: " << header.dll_characteristics << std::endl
    << "Size of Stack Reserve: " << header.size_of_stack_reserve << std::endl
    << "Size of Stack Commit: " << header.size_of_stack_commit << std::endl
    << "Size of Heap Reserve: " << header.size_of_heap_reserve << std::endl
    << "Size of Heap Commit: " << header.size_of_heap_commit << std::endl
    << "Loader Flags: " << header.loader_flags << std::endl
    << "Number of Rva and Size: " << header.number_of_rva_and_sizes << std::endl;

  return out;
}

}
