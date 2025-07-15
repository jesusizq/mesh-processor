#ifndef MESH_PROCESSOR_I_BASE_CONTROLLER_H
#define MESH_PROCESSOR_I_BASE_CONTROLLER_H

#include "httplib.h"

namespace controllers {

class IBaseController {
public:
  virtual ~IBaseController() = default;
  virtual void registerRoutes(httplib::Server &server) = 0;

protected:
  // Shared CORS handler for OPTIONS requests
  static void setupCorsOptions(httplib::Server &server,
                               const std::string &route) {
    server.Options(
        route, [](const httplib::Request &req, httplib::Response &res) {
          res.set_header("Access-Control-Allow-Origin", "*");
          res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
          res.set_header("Access-Control-Allow-Headers", "Content-Type");
          res.status = 200;
        });
  }
};

} // namespace controllers

#endif // MESH_PROCESSOR_I_BASE_CONTROLLER_H
