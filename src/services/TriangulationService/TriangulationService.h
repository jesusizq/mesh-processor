#ifndef MESH_PROCESSOR_TRIANGULATION_SERVICE_H
#define MESH_PROCESSOR_TRIANGULATION_SERVICE_H

#include "triangulation.h"

namespace services {

class TriangulationService {
public:
  TriangulationService() = default;

  triangulation::Triangles
  triangulate(const triangulation::Polygon &polygon) const;
};

} // namespace services

#endif // MESH_PROCESSOR_TRIANGULATION_SERVICE_H