#pragma once

namespace exe_inject {

class ISettings {
public:
  virtual ~ISettings() = default;

  virtual auto Read(int argc, char** argv) -> void = 0;
  [[nodiscard]] virtual auto PatchingFilePath() const noexcept -> std::string = 0;
};

inline auto operator<<(std::ostream& stream, const ISettings& settings) noexcept -> std::ostream& {
  stream << "Patching PE: " << settings.PatchingFilePath() << std::endl;
  return stream;
}

}
