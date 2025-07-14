#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include <MeshProcessorApp.h>
#include <iostream>

int main() {
  auto console_logger = spdlog::stdout_color_mt("console");
  spdlog::set_default_logger(console_logger);
  spdlog::set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");

  meshprocessor::MeshProcessorApp app;
  app.run();
  return 0;
}
