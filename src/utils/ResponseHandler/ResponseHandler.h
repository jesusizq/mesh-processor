#ifndef MESH_PROCESSOR_RESPONSE_HANDLER_H
#define MESH_PROCESSOR_RESPONSE_HANDLER_H

#include "httplib.h"
#include "nlohmann/json.hpp"
#include <string>

namespace utils {

enum class HttpStatus {
  OK = 200,
  CREATED = 201,
  NO_CONTENT = 204,
  BAD_REQUEST = 400,
  NOT_FOUND = 404,
  INTERNAL_SERVER_ERROR = 500
};

class ResponseHandler {
public:
  static void sendJson(httplib::Response &res, const nlohmann::json &jsonData,
                       HttpStatus status = HttpStatus::OK);
  static void sendError(httplib::Response &res, const std::string &message,
                        HttpStatus status);
  static void sendEmpty(httplib::Response &res,
                        HttpStatus status = HttpStatus::NO_CONTENT);
};

} // namespace utils

#endif // MESH_PROCESSOR_RESPONSE_HANDLER_H