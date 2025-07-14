#ifndef MESH_PROCESSOR_APP_H
#define MESH_PROCESSOR_APP_H

#include "IBaseController.h"
#include "httplib.h"
#include <memory>
#include <vector>

namespace meshprocessor {

class MeshProcessorApp {
public:
  MeshProcessorApp();
  void run();

private:
  void setupControllers();
  void registerRoutes();

  httplib::Server m_server;
  std::vector<std::shared_ptr<controllers::IBaseController>> m_controllers;
};

} // namespace meshprocessor

#endif // MESH_PROCESSOR_APP_H
