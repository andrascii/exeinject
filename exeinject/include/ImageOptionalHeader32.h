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
    << "\t\tMagic: PE32" << std::endl
    << "\t\tMajor Linker Version: " << header.major_linker_version << std::endl
    << "\t\tMinor Linker Version: " << header.minor_linker_version << std::endl
    << "\t\tSize of Code: " << header.size_of_code << std::endl
    << "\t\tSize of Initialized Data: " << header.size_of_initialized_data << std::endl
    << "\t\tSize of Uninitialized Data: " << header.size_of_uninitialized_data << std::endl
    << "\t\tAddress of Entry Point: " << std::hex << std::showbase << header.address_of_entry_point << std::endl
    << "\t\tBase of Code: " << std::hex << std::showbase << header.base_of_code << std::endl
    << "\t\tBase of Data: " << std::hex << std::showbase << header.base_of_data << std::endl
    << "\t\tImage Base: " << std::hex << std::showbase << header.image_base << std::endl
    << "\t\tSection Alignment: " << header.section_alignment << std::endl
    << "\t\tFile Alignment: " << header.file_alignment << std::endl
    << "\t\tMajor OS Version: " << header.major_operating_system_version << std::endl
    << "\t\tMinor OS Version: " << header.minor_operating_system_version << std::endl
    << "\t\tMajor Image Version: " << header.major_image_version << std::endl
    << "\t\tMinor Image Version: " << header.minor_image_version << std::endl
    << "\t\tMajor Subsystem Version: " << header.major_subsystem_version << std::endl
    << "\t\tMinor Subsystem Version: " << header.minor_subsystem_version << std::endl
    << "\t\tWin32 Version Value: " << header.win32_version_value << std::endl
    << "\t\tSize of Image: " << header.size_of_image << std::endl
    << "\t\tSize of Headers: " << header.size_of_headers << std::endl
    << "\t\tCheck Sum: " << header.check_sum << std::endl
    << "\t\tSubsystem: " << header.subsystem << std::endl
    << "\t\tDll Characteristics: " << header.dll_characteristics << std::endl
    << "\t\tSize of Stack Reserve: " << header.size_of_stack_reserve << std::endl
    << "\t\tSize of Stack Commit: " << header.size_of_stack_commit << std::endl
    << "\t\tSize of Heap Reserve: " << header.size_of_heap_reserve << std::endl
    << "\t\tSize of Heap Commit: " << header.size_of_heap_commit << std::endl
    << "\t\tLoader Flags: " << header.loader_flags << std::endl
    << "\t\tNumber of Rva and Size: " << header.number_of_rva_and_sizes << std::endl;

  return out;
}

}
