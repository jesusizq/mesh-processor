#include "httplib.h"
#include "nlohmann/json.hpp"
#include "triangulation.h"
#include <iostream>

int main() {
  httplib::Server svr;

  svr.Post("/triangulate", [](const httplib::Request &req,
                              httplib::Response &res) {
    try {
      // Parse the request body as JSON
      nlohmann::json input_json = nlohmann::json::parse(req.body);

      // Convert JSON to a polygon
      triangulation::Polygon polygon =
          triangulation::points_from_json(input_json);

      // Perform triangulation
      triangulation::Triangulator triangulator;
      triangulation::Triangles triangles = triangulator.triangulate(polygon);

      // Serialize the result to JSON
      nlohmann::json output_json = triangulation::triangles_to_json(triangles);

      // Send the response
      res.set_content(output_json.dump(), "application/json");
    } catch (const nlohmann::json::parse_error &e) {
      res.status = 400; // Bad Request
      res.set_content("Invalid JSON format: " + std::string(e.what()),
                      "text/plain");
    } catch (const std::exception &e) {
      res.status = 500; // Internal Server Error
      res.set_content("Error during triangulation: " + std::string(e.what()),
                      "text/plain");
    }
  });

  int port = 8080;
  std::cout << "Server starting on port " << port << std::endl;
  svr.listen("0.0.0.0", port);

  return 0;
}