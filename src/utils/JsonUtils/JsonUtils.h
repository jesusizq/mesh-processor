#ifndef MESH_PROCESSOR_JSON_UTILS_H
#define MESH_PROCESSOR_JSON_UTILS_H

#include "nlohmann/json.hpp"
#include "triangulation.h"

namespace utils {

class JsonUtils {
public:
  static triangulation::Polygon jsonToPolygon(const nlohmann::json &jsonData);

  static nlohmann::json polygonToJson(const triangulation::Polygon &polygon);

  static nlohmann::json
  indicesToJson(const triangulation::Indices &indices,
                const triangulation::Polygon &originalPolygon);
};

} // namespace utils

#endif // MESH_PROCESSOR_JSON_UTILS_H
