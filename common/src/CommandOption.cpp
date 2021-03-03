#include "CommandOption.h"

namespace common {

CommandOption::CommandOption(
  const std::string& short_name,
  const std::string& verbose_name,
  const std::string& description)
  : short_name_(short_name),
    verbose_name_(verbose_name),
    description_(description),
    valueless_(false) {}

auto CommandOption::DefaultValue() const noexcept -> const std::string& {
  return default_value_;
}

auto CommandOption::SetDefaultValue(const std::string& value) noexcept -> void {
  default_value_ = value;
}

auto CommandOption::Valueless() const noexcept -> bool {
  return valueless_;
}

auto CommandOption::SetValueless(bool value) noexcept -> void {
  valueless_ = value;
}

auto CommandOption::ShortName() const noexcept -> const std::string& {
  return short_name_;
}

auto CommandOption::VerboseName() const noexcept -> const std::string& {
  return verbose_name_;
}

auto CommandOption::Description() const noexcept -> const std::string& {
  return description_;
}

}
