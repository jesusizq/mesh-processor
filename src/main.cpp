#include "MeshProcessorApp/MeshProcessorApp.h"
#include "spdlog/spdlog.h"

int main() {
  auto console_logger = spdlog::stdout_color_mt("console");
  spdlog::set_default_logger(console_logger);
  spdlog::set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");
  spdlog::set_level(spdlog::level::info);

  meshprocessor::MeshProcessorApp app;
  app.run();

  return 0;
}