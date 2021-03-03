#include "Settings.h"
#include "Application.h"

namespace {

auto CreateSettings(int argc, char** argv) -> std::unique_ptr<exe_inject::ISettings> {
  auto settings = std::make_unique<exe_inject::Settings>();
  settings->Read(argc, argv);
  std::cout << *settings << std::endl;
  return settings;
}

}

int main(int argc, char** argv) {
  using namespace exe_inject;

  try {
    const auto application = Application{ CreateSettings(argc, argv) };
    application.Start();
    return EXIT_SUCCESS;
  } catch (const HelpMessageRequested& error) {
    std::cout << error.what();
    return EXIT_SUCCESS;
  } catch (const std::exception& error) {
    std::cerr << error.what() << std::endl;
    return EXIT_FAILURE;
  }
}
