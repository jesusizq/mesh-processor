#include "MeshProcessorApp.h"
#include "TriangulationController/TriangulationController.h"
#include "TriangulationService.h"
#include "spdlog/spdlog.h"

namespace meshprocessor {

MeshProcessorApp::MeshProcessorApp(
    std::vector<std::shared_ptr<controllers::IBaseController>> controllers)
    : m_controllers{std::move(controllers)} {
  registerRoutes();
}

void MeshProcessorApp::registerRoutes() {
  for (const auto &controller : m_controllers) {
    controller->registerRoutes(m_server);
  }
}

void MeshProcessorApp::run() {
  constexpr int port{8080};
  spdlog::info("MeshProcessorApp: Server starting on port {}", port);
  m_server.listen("0.0.0.0", port);
}

} // namespace meshprocessor
