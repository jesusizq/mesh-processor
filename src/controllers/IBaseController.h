#ifndef MESH_PROCESSOR_I_BASE_CONTROLLER_H
#define MESH_PROCESSOR_I_BASE_CONTROLLER_H

#include "httplib.h"

namespace controllers {

class IBaseController {
public:
  virtual ~IBaseController() = default;
  virtual void registerRoutes(httplib::Server &server) = 0;
};

} // namespace controllers

#endif // MESH_PROCESSOR_I_BASE_CONTROLLER_H
