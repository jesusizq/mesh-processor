#include "TriangulationService.h"
#include "triangulation.h"
#include <algorithm>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

class TriangulationServiceTest : public ::testing::Test {
protected:
  void SetUp() override {
    // A simple square polygon
    m_squarePolygon = {{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}};
  }

  triangulation::Polygon m_squarePolygon;
  services::TriangulationService m_service;
};

TEST_F(TriangulationServiceTest,
       Triangulate_SquarePolygon_ReturnsTwoTriangles) {
  auto result = m_service.triangulate(m_squarePolygon);

  // For a square, we expect 2 triangles (6 indices)
  EXPECT_EQ(result.size(), 6);
  EXPECT_EQ(result.size() % 3, 0); // Must be multiple of 3

  // Verify all indices are valid (within polygon bounds)
  for (const auto &idx : result) {
    EXPECT_LT(idx, m_squarePolygon.size());
  }

  // Verify we have exactly 2 triangles
  size_t num_triangles = result.size() / 3;
  EXPECT_EQ(num_triangles, 2);
}