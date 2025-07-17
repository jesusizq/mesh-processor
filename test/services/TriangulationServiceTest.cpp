#include "TriangulationService.h"
#include "triangulation.h"
#include <algorithm>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

class TriangulationServiceTest : public ::testing::Test {
protected:
  void SetUp() override {
    m_squarePolygon = {{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}};
    m_selfIntersectingPolygon = {
        {0.0, 0.0}, {2.0, 2.0}, {2.0, 0.0}, {0.0, 2.0}}; // Figure-8 shape
  }

  triangulation::Polygon m_squarePolygon;
  triangulation::Polygon m_selfIntersectingPolygon;
  services::TriangulationService m_service;
};

TEST_F(TriangulationServiceTest,
       TriangulateWithVertices_SquarePolygon_ReturnsVerticesAndIndices) {
  auto result = m_service.triangulateWithVertices(m_squarePolygon);

  // For a simple square (no self-intersections), vertices should be the same as
  // input
  EXPECT_EQ(result.vertices.size(), m_squarePolygon.size());
  EXPECT_EQ(result.indices.size(), 6);     // 2 triangles = 6 indices
  EXPECT_EQ(result.indices.size() % 3, 0); // Must be multiple of 3

  // Verify all indices are valid (within resolved vertices bounds)
  for (const auto &idx : result.indices) {
    EXPECT_LT(idx, result.vertices.size());
  }

  // For a simple polygon, vertices should match the input
  for (size_t i = 0; i < result.vertices.size(); ++i) {
    EXPECT_DOUBLE_EQ(triangulation::x(result.vertices[i]),
                     triangulation::x(m_squarePolygon[i]));
    EXPECT_DOUBLE_EQ(triangulation::y(result.vertices[i]),
                     triangulation::y(m_squarePolygon[i]));
  }
}

TEST_F(TriangulationServiceTest,
       TriangulateWithVertices_SelfIntersectingPolygon_ResolvesIntersections) {
  auto result = m_service.triangulateWithVertices(m_selfIntersectingPolygon);

  // Self-intersecting polygon should be resolved into more vertices
  EXPECT_GT(result.vertices.size(), 0);
  EXPECT_GT(result.indices.size(), 0);
  EXPECT_EQ(result.indices.size() % 3, 0); // Must be multiple of 3

  // Verify all indices are valid (within resolved vertices bounds)
  for (const auto &idx : result.indices) {
    EXPECT_LT(idx, result.vertices.size());
  }

  // Self-intersecting polygon should produce multiple triangles
  size_t numTriangles = result.indices.size() / 3;
  EXPECT_GT(numTriangles, 0);

  std::cout << "Self-intersecting polygon resolved into:" << std::endl;
  std::cout << "  - " << result.vertices.size() << " vertices" << std::endl;
  std::cout << "  - " << numTriangles << " triangles" << std::endl;
}

TEST_F(TriangulationServiceTest,
       TriangulateWithVertices_EmptyPolygon_ReturnsEmpty) {
  triangulation::Polygon emptyPolygon;
  auto result = m_service.triangulateWithVertices(emptyPolygon);

  EXPECT_TRUE(result.vertices.empty());
  EXPECT_TRUE(result.indices.empty());
}

TEST_F(TriangulationServiceTest,
       TriangulateWithVertices_TwoPointPolygon_ReturnsEmpty) {
  triangulation::Polygon twoPointPolygon = {{0.0, 0.0}, {1.0, 1.0}};
  auto result = m_service.triangulateWithVertices(twoPointPolygon);

  // Can't triangulate with less than 3 points
  EXPECT_TRUE(result.indices.empty());
}