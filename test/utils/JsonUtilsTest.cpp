#include "JsonUtils.h"
#include "nlohmann/json.hpp"
#include "triangulation.h"
#include <gtest/gtest.h>

class JsonUtilsTest : public ::testing::Test {
protected:
  void SetUp() override {
    m_squarePolygon = {{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}};

    // JSON representation of the square
    m_squareJson = nlohmann::json::array();
    m_squareJson.push_back({0.0, 0.0});
    m_squareJson.push_back({1.0, 0.0});
    m_squareJson.push_back({1.0, 1.0});
    m_squareJson.push_back({0.0, 1.0});

    // Simple triangulation result (two triangles from the square)
    m_triangulationResult = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}},
                             {{0.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

    m_triangulationJson = nlohmann::json::array();
    m_triangulationJson.push_back(
        createTriangleJson({{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}}}));
    m_triangulationJson.push_back(
        createTriangleJson({{{0.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}));
  }

  // JSON representation of the triangulation
  nlohmann::json
  createTriangleJson(const std::array<std::array<double, 2>, 3> &triangle) {
    nlohmann::json triangleJson;
    triangleJson.push_back({triangle[0][0], triangle[0][1]});
    triangleJson.push_back({triangle[1][0], triangle[1][1]});
    triangleJson.push_back({triangle[2][0], triangle[2][1]});
    return triangleJson;
  };

  triangulation::Polygon m_squarePolygon;
  nlohmann::json m_squareJson;
  triangulation::Triangles m_triangulationResult;
  nlohmann::json m_triangulationJson;
};

TEST_F(JsonUtilsTest, JsonToPolygon_ValidInput_ReturnsCorrectPolygon) {
  const auto result{utils::JsonUtils::jsonToPolygon(m_squareJson)};
  EXPECT_EQ(result.size(), m_squarePolygon.size());

  for (size_t i = 0; i < result.size(); ++i) {
    EXPECT_EQ(result[i][0], m_squarePolygon[i][0]);
    EXPECT_EQ(result[i][1], m_squarePolygon[i][1]);
  }
}

TEST_F(JsonUtilsTest, PolygonToJson_ValidPolygon_ReturnsCorrectJson) {
  auto result = utils::JsonUtils::polygonToJson(m_squarePolygon);
  EXPECT_EQ(result.size(), m_squareJson.size());

  for (size_t i = 0; i < result.size(); ++i) {
    EXPECT_EQ(result[i][0], m_squareJson[i][0]);
    EXPECT_EQ(result[i][1], m_squareJson[i][1]);
  }
}

TEST_F(JsonUtilsTest, TrianglesToJson_ValidTriangles_ReturnsCorrectJson) {
  auto result = utils::JsonUtils::trianglesToJson(m_triangulationResult);
  EXPECT_EQ(result.size(), m_triangulationJson.size());

  for (size_t i = 0; i < result.size(); ++i) {
    EXPECT_EQ(result[i].size(), m_triangulationJson[i].size());

    for (size_t j = 0; j < result[i].size(); ++j) {
      EXPECT_EQ(result[i][j][0], m_triangulationJson[i][j][0]);
      EXPECT_EQ(result[i][j][1], m_triangulationJson[i][j][1]);
    }
  }
}
