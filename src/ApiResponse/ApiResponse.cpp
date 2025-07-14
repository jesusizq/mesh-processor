#include "ApiResponse.h"

namespace meshprocessor {

ApiResponse::ApiResponse(bool isSuccess, std::string_view message)
    : isSuccess(isSuccess), message(message) {}

void ApiResponse::detail(std::string_view key, const nlohmann::json &value) {
  details[key] = value;
}

nlohmann::json ApiResponse::toJson() const {
  nlohmann::json response;
  response["success"] = isSuccess;
  response["message"] = message;
  if (!details.empty()) {
    response["details"] = details;
  }
  return response;
}

ApiResponse ApiResponse::success(std::string_view message) {
  return ApiResponse(true, message);
}

ApiResponse ApiResponse::error(std::string_view error) {
  return ApiResponse(false, error);
}
} // namespace meshprocessor