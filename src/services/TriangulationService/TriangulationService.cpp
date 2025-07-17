#include "TriangulationService.h"

namespace services {

TriangulationResult TriangulationService::triangulateWithVertices(
    const triangulation::Polygon &polygon) const {
  triangulation::Triangulator triangulator;
  TriangulationResult result;
  result.indices = triangulator.triangulate(polygon, result.vertices);
  return result;
}

} // namespace services