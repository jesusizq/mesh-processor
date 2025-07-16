#include "TriangulationService.h"

namespace services {

triangulation::Indices
TriangulationService::triangulate(const triangulation::Polygon &polygon) const {
  triangulation::Triangulator triangulator;
  return triangulator.triangulate(polygon);
}

} // namespace services