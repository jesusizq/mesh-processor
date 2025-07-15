#include "ResponseHandler.h"

namespace utils {

void ResponseHandler::sendJson(httplib::Response &res,
                               const nlohmann::json &jsonData,
                               HttpStatus status) {
  res.status = static_cast<int>(status);
  res.set_header("Access-Control-Allow-Origin", "*");
  res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
  res.set_header("Access-Control-Allow-Headers", "Content-Type");
  res.set_content(jsonData.dump(), "application/json");
}

void ResponseHandler::sendError(httplib::Response &res,
                                const std::string &message, HttpStatus status) {
  nlohmann::json errorJson;
  errorJson["error"] = message;
  res.status = static_cast<int>(status);
  res.set_header("Access-Control-Allow-Origin", "*");
  res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
  res.set_header("Access-Control-Allow-Headers", "Content-Type");
  res.set_content(errorJson.dump(), "application/json");
}

void ResponseHandler::sendEmpty(httplib::Response &res, HttpStatus status) {
  res.status = static_cast<int>(status);
  res.set_content("", "text/plain");
}

} // namespace utils