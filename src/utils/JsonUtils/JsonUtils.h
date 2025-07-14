#ifndef MESH_PROCESSOR_JSON_UTILS_H
#define MESH_PROCESSOR_JSON_UTILS_H

#include "nlohmann/json.hpp"
#include "triangulation.h"

namespace utils {

class JsonUtils {
public:
  static triangulation::Polygon json_to_polygon(const nlohmann::json &jsonData);

  static nlohmann::json polygon_to_json(const triangulation::Polygon &polygon);

  static nlohmann::json
  triangles_to_json(const triangulation::Triangles &triangles);
};

} // namespace utils

#endif // MESH_PROCESSOR_JSON_UTILS_H
