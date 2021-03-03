#pragma once

namespace exe_inject {

constexpr auto kImageSizeofShortName = 8;

struct ImageSectionHeader {
  uint8_t name[kImageSizeofShortName];

  union {
    uint32_t physical_address;
    uint32_t virtual_size;
  } misc;

  uint32_t virtual_address;
  uint32_t size_of_raw_data;
  uint32_t pointer_to_raw_data;
  uint32_t pointer_to_relocations;
  uint32_t pointer_to_line_numbers;
  uint16_t number_of_relocations;
  uint16_t number_of_line_numbers;
  uint32_t characteristics;
};

using Sections = std::vector<ImageSectionHeader>;

inline auto operator<<(std::ostream& out, const ImageSectionHeader& section) noexcept -> std::ostream& {
  out
    << "Name: " << section.name << std::endl
    << "Virtual Address: " << section.virtual_address << std::endl
    << "Size of Raw Data: " << section.size_of_raw_data << std::endl
    << "Pointer to Raw Data: " << section.pointer_to_raw_data << std::endl
    << "Pointer to Relocations: " << section.pointer_to_relocations << std::endl
    << "Pointer to Line Numbers: " << section.pointer_to_line_numbers << std::endl
    << "Number of Relocations: " << section.number_of_relocations << std::endl
    << "Number of Line Numbers: " << section.number_of_line_numbers << std::endl
    << "Characteristics: " << section.characteristics << std::endl;

  return out;
}

}
