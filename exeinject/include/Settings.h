#pragma once

#include "ISettings.h"
#include "CommandLineOptions.h"

namespace exe_inject {

struct HelpMessageRequested : std::runtime_error { using std::runtime_error::runtime_error; };

class Settings final : public ISettings {
public:
  auto Read(int argc, char** argv) -> void override;
  auto PatchingFilePath() const noexcept -> std::string override;

private:
  std::unique_ptr<common::CommandLineOptions> parser_;
};

}
