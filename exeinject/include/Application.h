#pragma once

#include "ISettings.h"

namespace exe_inject {

class Application final {
public:
  explicit Application(std::unique_ptr<ISettings> settings);

  auto Start() const -> void;

private:
  std::unique_ptr<ISettings> settings_;
};

}
