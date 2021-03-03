#pragma once

namespace common {

class CommandOption {
public:
  CommandOption(
    const std::string& short_name,
    const std::string& verbose_name,
    const std::string& description);

  auto DefaultValue() const noexcept -> const std::string&;
  auto SetDefaultValue(const std::string& value) noexcept -> void;

  auto Valueless() const noexcept -> bool;
  auto SetValueless(bool value) noexcept -> void;

  auto ShortName() const noexcept -> const std::string&;
  auto VerboseName() const noexcept -> const std::string&;
  auto Description() const noexcept -> const std::string&;

private:
  std::string short_name_;
  std::string verbose_name_;
  std::string description_;
  std::string default_value_;
  bool valueless_;
};

}
