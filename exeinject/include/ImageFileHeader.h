#pragma once

#include "Helpers.h"

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
  const auto timestamp = common::Helpers::FromUtcSec(header.time_date_stamp);
  const auto time_breakdown = std::chrono::system_clock::to_time_t(timestamp);

  out
    << "\t\tMachine: " << header.machine << std::endl
    << "\t\tNumber of Sections: " << header.number_of_sections << std::endl
    << "\t\tTime Date Stamp: " << std::put_time(std::localtime(&time_breakdown), "%F %T") << std::endl
    << "\t\tPointer to Symbol Table: " << header.pointer_to_symbol_table << std::endl
    << "\t\tNumber of Symbols: " << header.number_of_symbols << std::endl
    << "\t\tSize of Optional Header: " << header.size_of_optional_header << std::endl
    << "\t\tCharacteristics: " << header.characteristics << std::endl;

  return out;
}

}
