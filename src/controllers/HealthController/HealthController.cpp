#include "HealthController.h"
#include "ResponseHandler.h"
#include "nlohmann/json.hpp"
#include "spdlog/spdlog.h"
#include <ctime>

namespace controllers {

void HealthController::registerRoutes(httplib::Server &server) {
  server.Get("/health",
             [this](const httplib::Request &req, httplib::Response &res) {
               this->getHealth(req, res);
             });

  setupCorsOptions(server, "/health");
}

void HealthController::getHealth(const httplib::Request &req,
                                 httplib::Response &res) {
  try {
    spdlog::debug("Health check requested");

    nlohmann::json health;
    health["status"] = "healthy";
    health["service"] = "mesh-processor";
    health["timestamp"] = std::time(nullptr);
    health["version"] = "1.0.0";

    utils::ResponseHandler::sendJson(res, health);
    spdlog::debug("Health check response sent successfully");

  } catch (const std::exception &e) {
    const auto errMsg{"Error during health check: " + std::string(e.what())};
    spdlog::error(errMsg);
    utils::ResponseHandler::sendError(res, errMsg,
                                      utils::HttpStatus::INTERNAL_SERVER_ERROR);
  }
}

} // namespace controllers