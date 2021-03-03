#pragma once

#include "CommandOption.h"

namespace common {

class CommandLineOptions {
public:
  auto Parse(int argc, char** argv) -> void;
  auto RegisterOption(const CommandOption& option) noexcept -> void;

  [[nodiscard]] auto OptionValue(const CommandOption& option) const -> std::string;
  [[nodiscard]] auto HasOption(const CommandOption& option) const -> bool;

  auto HelpMessage() const noexcept -> std::string;

private:
  [[nodiscard]] auto OptionMeta(const CommandOption& option) const -> boost::program_options::typed_value<std::string>*;
  static auto CommandOptionFormatted(const CommandOption& option) -> std::string;

private:
  boost::program_options::options_description options_description_;
  boost::program_options::variables_map variables_map_;
  std::vector<CommandOption> options_{};
};

}
