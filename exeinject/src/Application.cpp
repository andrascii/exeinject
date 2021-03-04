#include "Application.h"
#include "PeParser.h"

namespace exe_inject {

Application::Application(std::unique_ptr<ISettings> settings)
  : settings_{ std::move(settings) } {}

auto Application::Start() const -> void {
  const auto path = std::filesystem::path{ settings_->PatchingFilePath() };

  if (!exists(path)) {
    throw std::runtime_error{ "Patching PE not found" };
  }

  const auto parser = PeParser{};
  [[maybe_unused]] const auto& [image_nt_headers, sections, imports] = parser.Parse(path);

  std::cout << "File Header Info: " << std::endl << std::endl
    << image_nt_headers.image_file_header << std::endl;

  if (image_nt_headers.image_file_header.size_of_optional_header) {
    std::visit([](const auto& header) {
      std::cout << "PE Header Info: " << std::endl << std::endl;
      std::cout << header << std::endl;
    }, image_nt_headers.image_optional_header);
  }

  if (!sections.empty()) {
    std::cout << "Sections:" << std::endl << std::endl;

    copy(
      begin(sections),
      end(sections),
      std::ostream_iterator<ImageSectionHeader>{ std::cout, "\n" }
    );
  }

  if (!imports.empty()) {
    std::cout << "Imports:" << std::endl << std::endl;

    for (const auto& [module_name, import_functions] : imports) {
      std::cout << "\t" << module_name << std::endl;

      for (const auto& import_function : import_functions) {
        std::cout << "\t\t" << import_function << std::endl;
      }

      std::cout << std::endl;
    }
  }
}

}
