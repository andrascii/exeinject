#include "Settings.h"
#include "CommandOption.h"

namespace {

const common::CommandOption& PatchingFilePathOption() {
  static common::CommandOption option{ "f", "file", "Patching file path" };
  return option;
}

}

namespace exe_inject {

auto Settings::Read(int argc, char** argv) -> void {
  std::vector<std::reference_wrapper<const common::CommandOption>> required_options{};

  common::CommandOption help_option{ "h", "help", "Produce help message" };
  help_option.SetValueless(true);

  required_options.push_back(std::cref(PatchingFilePathOption()));

  parser_ = std::make_unique<common::CommandLineOptions>();
  parser_->RegisterOption(PatchingFilePathOption());
  parser_->Parse(argc, argv);

  if (parser_->HasOption(help_option)) {
    throw HelpMessageRequested{ parser_->HelpMessage() };
  }

  for (const auto& required_option : required_options) {
    if (!parser_->HasOption(required_option)) {
      throw boost::program_options::required_option{ required_option.get().VerboseName() };
    }
  }
}

auto Settings::PatchingFilePath() const noexcept -> std::string {
  return parser_->OptionValue(PatchingFilePathOption());
}

}