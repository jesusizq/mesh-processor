#ifndef MESH_PROCESSOR_TRIANGULATION_SERVICE_H
#define MESH_PROCESSOR_TRIANGULATION_SERVICE_H

#include "triangulation.h"

namespace services {

struct TriangulationResult {
  triangulation::Polygon vertices;
  triangulation::Indices indices;
};

class TriangulationService {
public:
  TriangulationService() = default;
  virtual ~TriangulationService() = default;

  virtual TriangulationResult
  triangulateWithVertices(const triangulation::Polygon &polygon) const;
};

} // namespace services

#endif // MESH_PROCESSOR_TRIANGULATION_SERVICE_H