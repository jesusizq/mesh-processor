#include "JsonUtils.h"
#include "spdlog/spdlog.h"

namespace utils {

triangulation::Polygon
JsonUtils::jsonToPolygon(const nlohmann::json &jsonData) {
  triangulation::Polygon polygon;

  if (jsonData.is_array()) {
    polygon.reserve(jsonData.size());
    for (const auto &item : jsonData) {
      if (item.is_array() && item.size() == 2 && item[0].is_number() &&
          item[1].is_number()) {
        polygon.emplace_back(
            triangulation::Point{item[0].get<double>(), item[1].get<double>()});
      } else {
        const auto errMsg{"Invalid point format in JSON array"};
        spdlog::error(errMsg);
        throw std::invalid_argument(errMsg);
      }
    }
  } else {
    const auto errMsg{"JSON data is not an array"};
    spdlog::error(errMsg);
    throw std::invalid_argument(errMsg);
  }
  return polygon;
}

nlohmann::json
JsonUtils::indicesToJson(const triangulation::Indices &indices,
                         const triangulation::Polygon &originalPolygon) {
  // Return the indices as a flat array, consistent with WASM output
  nlohmann::json jsonIndices = nlohmann::json::array();
  for (const auto &index : indices) {
    jsonIndices.push_back(index);
  }
  return jsonIndices;
}

nlohmann::json JsonUtils::polygonToJson(const triangulation::Polygon &polygon) {
  nlohmann::json jsonPolygon;
  for (const auto &point : polygon) {
    jsonPolygon.push_back({triangulation::x(point), triangulation::y(point)});
  }
  return jsonPolygon;
}

} // namespace utils
