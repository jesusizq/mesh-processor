#include "TriangulationService.h"
#include "triangulation.h"
#include <algorithm>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

// Custom matcher for unordered equality of points within a triangle
MATCHER_P(UnorderedTriangleEq, expected_triangle, "") {
  return ::testing::UnorderedElementsAre(
             expected_triangle[0], expected_triangle[1], expected_triangle[2])
      .MatchAndExplain(arg, result_listener);
}

class TriangulationServiceTest : public ::testing::Test {
protected:
  void SetUp() override {
    // A simple square polygon
    m_squarePolygon = {{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}};

    // Expected triangulation results (two possible ways to triangulate a
    // square)
    m_expectedTriangles1 = {{{0.0, 0.0}, {1.0, 0.0}, {0.0, 1.0}},
                            {{1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

    m_expectedTriangles2 = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}},
                            {{0.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
  }

  triangulation::Polygon m_squarePolygon;
  triangulation::Triangles m_expectedTriangles1;
  triangulation::Triangles m_expectedTriangles2;
  services::TriangulationService m_service;
};

TEST_F(TriangulationServiceTest,
       Triangulate_SquarePolygon_ReturnsTwoTriangles) {
  auto result = m_service.triangulate(m_squarePolygon);
  EXPECT_EQ(result.size(), 2);

  // Check if the result matches one of the expected triangulations
  bool matches1 =
      result.size() == m_expectedTriangles1.size() &&
      std::is_permutation(
          result.begin(), result.end(), m_expectedTriangles1.begin(),
          [](const auto &a, const auto &b) {
            return std::is_permutation(a.begin(), a.end(), b.begin());
          });

  bool matches2 =
      result.size() == m_expectedTriangles2.size() &&
      std::is_permutation(
          result.begin(), result.end(), m_expectedTriangles2.begin(),
          [](const auto &a, const auto &b) {
            return std::is_permutation(a.begin(), a.end(), b.begin());
          });

  EXPECT_TRUE(matches1 || matches2)
      << "Triangulation result does not match any expected variant.";
}