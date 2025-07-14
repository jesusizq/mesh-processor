#ifndef API_RESPONSE_H
#define API_RESPONSE_H

#include <nlohmann/json.hpp>
#include <string_view>
#include <unordered_map>

namespace meshprocessor {

class ApiResponse {
public:
  ApiResponse(bool success, std::string_view message);

  void detail(std::string_view key, const nlohmann::json &value);
  nlohmann::json toJson() const;

  static ApiResponse success(std::string_view message);
  static ApiResponse error(std::string_view error);

private:
  bool isSuccess{false};
  std::string_view message;
  std::unordered_map<std::string_view, nlohmann::json> details;
};

} // namespace meshprocessor

#endif // API_RESPONSE_H