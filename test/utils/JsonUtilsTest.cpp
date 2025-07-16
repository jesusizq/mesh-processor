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

    // Indices for triangulation (two triangles from the square)
    // Triangle 1: indices 0, 1, 2 -> points (0,0), (1,0), (1,1)
    // Triangle 2: indices 0, 2, 3 -> points (0,0), (1,1), (0,1)
    m_triangulationIndices = {0, 1, 2, 0, 2, 3};

    // Expected JSON should now be a flat array of indices
    m_expectedTriangulationJson = nlohmann::json::array();
    for (const auto &index : m_triangulationIndices) {
      m_expectedTriangulationJson.push_back(index);
    }
  }

  triangulation::Polygon m_squarePolygon;
  nlohmann::json m_squareJson;
  triangulation::Indices m_triangulationIndices;
  nlohmann::json m_expectedTriangulationJson;
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

TEST_F(JsonUtilsTest, IndicesToJson_ValidIndices_ReturnsCorrectJson) {
  auto result =
      utils::JsonUtils::indicesToJson(m_triangulationIndices, m_squarePolygon);
  EXPECT_EQ(result.size(), m_expectedTriangulationJson.size());

  // Now comparing flat arrays of indices
  for (size_t i = 0; i < result.size(); ++i) {
    EXPECT_EQ(result[i], m_expectedTriangulationJson[i]);
  }
}
