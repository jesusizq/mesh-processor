#include "MeshProcessorApp.h"
#include "TriangulationController/TriangulationController.h"
#include "TriangulationService.h"
#include "spdlog/spdlog.h"

namespace meshprocessor {

MeshProcessorApp::MeshProcessorApp() {
  setupControllers();
  registerRoutes();
}

void MeshProcessorApp::setupControllers() {
  // Initialize services
  auto triangulationService{std::make_shared<services::TriangulationService>()};

  // Initialize controllers
  auto triangulationController{
      std::make_shared<controllers::TriangulationController>(
          triangulationService)};
  m_controllers.push_back(triangulationController);
}

void MeshProcessorApp::registerRoutes() {
  for (const auto &controller : m_controllers) {
    controller->registerRoutes(m_server);
  }
}

void MeshProcessorApp::run() {
  constexpr int port{8080};
  spdlog::info("Server starting on port {}", port);
  m_server.listen("0.0.0.0", port);
}

} // namespace meshprocessor
