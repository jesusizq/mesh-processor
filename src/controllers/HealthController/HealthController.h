#ifndef MESH_PROCESSOR_HEALTH_CONTROLLER_H
#define MESH_PROCESSOR_HEALTH_CONTROLLER_H

#include "IBaseController.h"

namespace controllers {

class HealthController : public IBaseController {
public:
  HealthController() = default;
  virtual ~HealthController() = default;

  void registerRoutes(httplib::Server &server) override;

private:
  void getHealth(const httplib::Request &req, httplib::Response &res);
};

} // namespace controllers

#endif // MESH_PROCESSOR_HEALTH_CONTROLLER_H