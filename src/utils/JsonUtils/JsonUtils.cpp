#include "JsonUtils.h"

namespace utils {

triangulation::Polygon
JsonUtils::json_to_polygon(const nlohmann::json &jsonData) {
  triangulation::Polygon polygon;
  polygon.reserve(jsonData.size());
  for (const auto &point : jsonData) {
    polygon.emplace_back(
        triangulation::Point{point[0].get<double>(), point[1].get<double>()});
  }
  return polygon;
}

nlohmann::json
JsonUtils::triangles_to_json(const triangulation::Triangles &triangles) {
  auto jsonTriangles = nlohmann::json::array();
  for (const auto &triangle : triangles) {
    auto jsonTriangle = nlohmann::json::array();
    for (const auto &point : triangle) {
      jsonTriangle.push_back(
          {triangulation::x(point), triangulation::y(point)});
    }
    jsonTriangles.push_back(jsonTriangle);
  }
  return jsonTriangles;
}

nlohmann::json
JsonUtils::polygon_to_json(const triangulation::Polygon &polygon) {
  nlohmann::json jsonPolygon;
  for (const auto &point : polygon) {
    jsonPolygon.push_back({triangulation::x(point), triangulation::y(point)});
  }
  return jsonPolygon;
}

} // namespace utils
