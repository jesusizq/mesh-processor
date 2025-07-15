#include "TriangulationService.h"

namespace services {

triangulation::Triangles
TriangulationService::triangulate(const triangulation::Polygon &polygon) const {
  triangulation::Triangulator triangulator;
  return triangulator.triangulate(polygon);
}

} // namespace services