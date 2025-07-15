add_library(ServicesTestSources OBJECT
    TriangulationServiceTest.cpp
)

target_include_directories(ServicesTestSources PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(ServicesTestSources PUBLIC
    gtest
    gmock
    TriangulationService
    libtriangulation
)

target_link_libraries(MeshProcessorTestSources INTERFACE $<TARGET_OBJECTS:ServicesTestSources>) 