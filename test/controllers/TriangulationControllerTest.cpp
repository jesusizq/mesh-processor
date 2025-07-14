#include "TriangulationController.h"
#include "JsonUtils.h"
#include "ResponseHandler.h"
#include "TriangulationService.h"
#include "httplib.h"
#include "nlohmann/json.hpp"
#include "triangulation.h"
#include <algorithm>
#include <functional>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

// Mock for TriangulationService
class MockTriangulationService : public services::TriangulationService {
public:
  MOCK_METHOD(triangulation::Triangles, triangulate,
              (const triangulation::Polygon &polygon), (const override));
};

class TriangulationControllerTest : public ::testing::Test {
protected:
  void SetUp() override {

    // Expected triangulation results
    m_expectedTriangles1 = {{{0.0, 0.0}, {1.0, 0.0}, {0.0, 1.0}},
                            {{1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

    m_expectedTriangles2 = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}},
                            {{0.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

    // JSON request body
    m_squarePolygon = {{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}};
    m_requestBody = nlohmann::json::array();
    m_requestBody.push_back(m_squarePolygon[0]);
    m_requestBody.push_back(m_squarePolygon[1]);
    m_requestBody.push_back(m_squarePolygon[2]);
    m_requestBody.push_back(m_squarePolygon[3]);

    m_mockService = std::make_shared<MockTriangulationService>();
    m_controller =
        std::make_unique<controllers::TriangulationController>(m_mockService);
  }

  triangulation::Polygon m_squarePolygon;
  triangulation::Triangles m_expectedTriangles1;
  triangulation::Triangles m_expectedTriangles2;
  nlohmann::json m_requestBody;
  std::shared_ptr<MockTriangulationService> m_mockService;
  std::unique_ptr<controllers::TriangulationController> m_controller;
  httplib::Request m_req;
  httplib::Response m_res;
};

TEST_F(TriangulationControllerTest, Triangulate_ValidRequest_ReturnsTriangles) {
  m_req.body = m_requestBody.dump();
  EXPECT_CALL(*m_mockService, triangulate(testing::_))
      .WillOnce(testing::Return(m_expectedTriangles1));

  m_controller->triangulate(m_req, m_res);

  EXPECT_EQ(m_res.status, static_cast<int>(utils::HttpStatus::OK));
  EXPECT_EQ(m_res.get_header_value("Content-Type"), "application/json");
  const auto responseJson = nlohmann::json::parse(m_res.body);

  // Convert response to Triangles for comparison
  triangulation::Triangles resultTriangles;
  for (const auto &triJson : responseJson) {
    resultTriangles.push_back(utils::JsonUtils::jsonToPolygon(triJson));
  }

  bool matches1 =
      resultTriangles.size() == m_expectedTriangles1.size() &&
      std::is_permutation(
          resultTriangles.begin(), resultTriangles.end(),
          m_expectedTriangles1.begin(), [](const auto &a, const auto &b) {
            return std::is_permutation(a.begin(), a.end(), b.begin());
          });

  bool matches2 =
      resultTriangles.size() == m_expectedTriangles2.size() &&
      std::is_permutation(
          resultTriangles.begin(), resultTriangles.end(),
          m_expectedTriangles2.begin(), [](const auto &a, const auto &b) {
            return std::is_permutation(a.begin(), a.end(), b.begin());
          });

  EXPECT_TRUE(matches1 || matches2)
      << "Triangulation result does not match any expected variant.";
}

TEST_F(TriangulationControllerTest, Triangulate_InvalidJson_ReturnsBadRequest) {
  m_req.body = "invalid json";

  m_controller->triangulate(m_req, m_res);

  EXPECT_EQ(m_res.status, static_cast<int>(utils::HttpStatus::BAD_REQUEST));
  const auto responseJson = nlohmann::json::parse(m_res.body);
  EXPECT_TRUE(responseJson.contains("error"));
}