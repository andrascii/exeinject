#pragma once

namespace exe_inject {

struct ImageFileHeader {
  uint16_t machine;
  uint16_t number_of_sections;
  uint32_t time_date_stamp;
  uint32_t pointer_to_symbol_table;
  uint32_t number_of_symbols;
  uint16_t size_of_optional_header;
  uint16_t characteristics;
};

inline auto operator<<(std::ostream& out, const ImageFileHeader& header) noexcept -> std::ostream& {
  out
    << "Machine: " << header.machine << std::endl
    << "Number of Sections: " << header.number_of_sections << std::endl
    << "Time Date Stamp: " << header.time_date_stamp << std::endl
    << "Pointer to Symbol Table: " << header.pointer_to_symbol_table << std::endl
    << "Number of Symbols: " << header.number_of_symbols << std::endl
    << "Size of Optional Header: " << header.size_of_optional_header << std::endl
    << "Characteristics: " << header.characteristics << std::endl;

  return out;
}

}
