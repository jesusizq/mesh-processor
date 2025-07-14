#include "MeshProcessorApp.h"
#include <triangulation.h>

namespace meshprocessor {

void MeshProcessorApp::run() {
  httplib::Server svr;
  setupRoutes(svr);
  spdlog::info(
      "Mesh Processor App started and listening at http://localhost:{}",
      m_port);
  svr.listen("0.0.0.0", m_port);
}

void MeshProcessorApp::setupRoutes(httplib::Server &svr) {

  svr.Post("/triangulate",
           [this](const httplib::Request &req, httplib::Response &res) {
             this->triangulate(req, res);
           });
}

void MeshProcessorApp::triangulate(const httplib::Request &req,
                                   httplib::Response &res) {
  try {
    // Parse the request body as JSON
    nlohmann::json input_json = nlohmann::json::parse(req.body);

    // Convert JSON to a polygon
    const auto polygon{triangulation::points_from_json(input_json)};

    // Perform triangulation
    triangulation::Triangulator triangulator;
    const auto triangles{triangulator.triangulate(polygon)};

    // Serialize the result to JSON
    nlohmann::json output_json = triangulation::triangles_to_json(triangles);

    auto succRes{ApiResponse::success("Triangulation successful.")};
    succRes.detail("triangles", output_json);
    setContentAsJson(res, succRes);
    spdlog::info("Triangulation successful.");
  } catch (const nlohmann::json::parse_error &e) {
    res.status = 400;
    auto errRes{
        ApiResponse::error("Invalid JSON format: " + std::string(e.what()))};
    setContentAsJson(res, errRes);
    spdlog::error("Invalid JSON format: {}", e.what());
  } catch (const std::exception &e) {
    res.status = 500;
    auto errRes{ApiResponse::error("Error during triangulation: " +
                                   std::string(e.what()))};
    setContentAsJson(res, errRes);
    spdlog::error("Error during triangulation: {}", e.what());
  }
}

} // namespace meshprocessor
