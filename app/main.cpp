#include "HealthController.h"
#include "MeshProcessorApp.h"
#include "TriangulationController.h"
#include "TriangulationService.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include <memory>
#include <vector>

int main() {
  const auto console_logger{spdlog::stdout_color_mt("console")};
  spdlog::set_default_logger(console_logger);
  spdlog::set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");
  spdlog::set_level(spdlog::level::info);

  // Create services and controllers
  auto triangulationService{std::make_shared<services::TriangulationService>()};
  auto triangulationController{
      std::make_shared<controllers::TriangulationController>(
          triangulationService)};
  auto healthController{std::make_shared<controllers::HealthController>()};

  // Gather controllers
  std::vector<std::shared_ptr<controllers::IBaseController>> controllers{
      triangulationController, healthController};

  // Run the app
  meshprocessor::MeshProcessorApp app(controllers);
  app.run();

  return 0;
}
