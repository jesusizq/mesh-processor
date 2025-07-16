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
  MOCK_METHOD(triangulation::Indices, triangulate,
              (const triangulation::Polygon &polygon), (const override));
};

class TriangulationControllerTest : public ::testing::Test {
protected:
  void SetUp() override {

    // Expected triangulation indices (two triangles from square)
    // Triangle 1: indices 0, 1, 2 -> points (0,0), (1,0), (1,1)
    // Triangle 2: indices 0, 2, 3 -> points (0,0), (1,1), (0,1)
    m_expectedIndices = {0, 1, 2, 0, 2, 3};

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
  triangulation::Indices m_expectedIndices;
  nlohmann::json m_requestBody;
  std::shared_ptr<MockTriangulationService> m_mockService;
  std::unique_ptr<controllers::TriangulationController> m_controller;
  httplib::Request m_req;
  httplib::Response m_res;
};

TEST_F(TriangulationControllerTest, Triangulate_ValidRequest_ReturnsTriangles) {
  m_req.body = m_requestBody.dump();
  EXPECT_CALL(*m_mockService, triangulate(testing::_))
      .WillOnce(testing::Return(m_expectedIndices));

  m_controller->triangulate(m_req, m_res);

  EXPECT_EQ(m_res.status, static_cast<int>(utils::HttpStatus::OK));
  EXPECT_EQ(m_res.get_header_value("Content-Type"), "application/json");
  const auto responseJson = nlohmann::json::parse(m_res.body);

  // Response should be a flat array of indices
  EXPECT_TRUE(responseJson.is_array());
  EXPECT_EQ(responseJson.size(),
            6); // Six indices (two triangles × 3 indices each)

  // Verify each index is a number
  for (const auto &index : responseJson) {
    EXPECT_TRUE(index.is_number());
    EXPECT_TRUE(index.is_number_integer());
    EXPECT_GE(index.get<int>(), 0); // Indices should be non-negative
  }
}

TEST_F(TriangulationControllerTest, Triangulate_InvalidJson_ReturnsBadRequest) {
  m_req.body = "invalid json";

  m_controller->triangulate(m_req, m_res);

  EXPECT_EQ(m_res.status, static_cast<int>(utils::HttpStatus::BAD_REQUEST));
  const auto responseJson = nlohmann::json::parse(m_res.body);
  EXPECT_TRUE(responseJson.contains("error"));
}