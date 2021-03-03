#include "CommandLineOptions.h"

namespace common {

auto CommandLineOptions::Parse(int argc, char** argv) -> void {
  const auto initialize_option = [this](const CommandOption& option) {
    auto option_initializer = options_description_.add_options();

    if (option.Valueless()) {
      option_initializer(CommandOptionFormatted(option).data(), option.Description().data());
    }
    else {
      option_initializer(CommandOptionFormatted(option).data(), OptionMeta(option), option.Description().data());
    }
  };

  std::for_each(options_.begin(), options_.end(), initialize_option);

  const auto parsed_command_line = boost::program_options::command_line_parser(argc, argv)
    .options(options_description_)
    .allow_unregistered()
    .run();

  store(parsed_command_line, variables_map_);
  notify(variables_map_);
}

auto CommandLineOptions::RegisterOption(const CommandOption& option) noexcept -> void {
  options_.push_back(option);
}

auto CommandLineOptions::OptionValue(const CommandOption& option) const -> std::string {
  if (variables_map_.count(option.ShortName()) != 0) {
    return variables_map_[option.ShortName()].as<std::string>();
  }
  if (variables_map_.count(option.VerboseName()) != 0) {
    return variables_map_[option.VerboseName()].as<std::string>();
  }

  return std::string();
}

auto CommandLineOptions::HasOption(const CommandOption& option) const -> bool {
  return variables_map_.count(option.ShortName()) != 0 ||
    variables_map_.count(option.VerboseName()) != 0;
}

auto CommandLineOptions::HelpMessage() const noexcept -> std::string {
  std::stringstream stream;
  stream << "Usage:" << std::endl;
  stream << options_description_ << std::endl;
  return stream.str();
}

auto CommandLineOptions::OptionMeta(const CommandOption& option) const -> boost::program_options::typed_value<std::string>* {
  auto meta = boost::program_options::value<std::string>();

  if (!option.DefaultValue().empty()) {
    meta->default_value(option.DefaultValue().data());
  }

  return meta;
}

auto CommandLineOptions::CommandOptionFormatted(const CommandOption& option) -> std::string {
  auto const short_name = option.ShortName();
  auto const verbose_name = option.VerboseName();

  if (!short_name.empty() && !verbose_name.empty()) {
    return verbose_name + "," + short_name;
  }

  if (!short_name.empty()) {
    return short_name.data();
  }

  return verbose_name;
}

}
