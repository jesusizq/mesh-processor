#ifndef MESHPROCESSORAPP_H
#define MESHPROCESSORAPP_H

#include "ApiResponse.h"
#include "httplib.h"
#include "spdlog/spdlog.h"

namespace meshprocessor {

class MeshProcessorApp {
public:
  MeshProcessorApp() = default;
  void run();

private:
  int m_port = 8080;

  void setupRoutes(httplib::Server &svr);

  void setContentAsJson(httplib::Response &res, ApiResponse &apiRes) {
    res.set_content(apiRes.toJson().dump(), "application/json");
  }

  void triangulate(const httplib::Request &req, httplib::Response &res);
};

} // namespace meshprocessor

#endif // MESHPROCESSORAPP_H
