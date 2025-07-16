#include "TriangulationController.h"
#include "JsonUtils.h"
#include "ResponseHandler.h"
#include "nlohmann/json.hpp"
#include "spdlog/spdlog.h"

namespace controllers {

TriangulationController::TriangulationController(
    std::shared_ptr<services::TriangulationService> triangulationService)
    : m_triangulationService(std::move(triangulationService)) {}

void TriangulationController::registerRoutes(httplib::Server &server) {
  server.Post("/triangulate",
              [this](const httplib::Request &req, httplib::Response &res) {
                this->triangulate(req, res);
              });

  setupCorsOptions(server, "/triangulate");
}

void TriangulationController::triangulate(const httplib::Request &req,
                                          httplib::Response &res) {
  try {
    spdlog::info("Received request to triangulate");
    nlohmann::json inputJson = nlohmann::json::parse(req.body);

    const auto polygon{utils::JsonUtils::jsonToPolygon(inputJson)};
    const auto indices{m_triangulationService->triangulate(polygon)};

    nlohmann::json outputJson =
        utils::JsonUtils::indicesToJson(indices, polygon);

    spdlog::info("Triangulation was successful");
    utils::ResponseHandler::sendJson(res, outputJson);

  } catch (const nlohmann::json::parse_error &e) {
    const auto errMsg{"Invalid JSON format: " + std::string(e.what())};
    spdlog::error(errMsg);
    utils::ResponseHandler::sendError(res, errMsg,
                                      utils::HttpStatus::BAD_REQUEST);
  } catch (const std::exception &e) {
    const auto errMsg{"Error during triangulation: " + std::string(e.what())};
    spdlog::error(errMsg);
    utils::ResponseHandler::sendError(res, errMsg,
                                      utils::HttpStatus::INTERNAL_SERVER_ERROR);
  }
}

} // namespace controllers
