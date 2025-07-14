#ifndef MESH_PROCESSOR_TRIANGULATION_CONTROLLER_H
#define MESH_PROCESSOR_TRIANGULATION_CONTROLLER_H

#include "IBaseController.h"
#include "TriangulationService.h"
#include <memory>

namespace controllers {

class TriangulationController : public IBaseController {
public:
  explicit TriangulationController(
      std::shared_ptr<services::TriangulationService> triangulationService);

  void registerRoutes(httplib::Server &server) override;

  void triangulate(const httplib::Request &req, httplib::Response &res);

private:
  std::shared_ptr<services::TriangulationService> m_triangulationService;
};

} // namespace controllers

#endif // MESH_PROCESSOR_TRIANGULATION_CONTROLLER_H
