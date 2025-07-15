add_library(MeshProcessorTestSources INTERFACE)

add_subdirectory(utils)
add_subdirectory(services)
add_subdirectory(controllers)

# Create the test executable and link it against GTest and our test sources.
add_executable(MeshProcessorTests main.cpp)
target_link_libraries(MeshProcessorTests PRIVATE 
    gtest_main
    gmock
    MeshProcessorTestSources
    MeshProcessorApp
    TriangulationController
    TriangulationService
    JsonUtils
    ResponseHandler
    spdlog::spdlog
    httplib
    nlohmann_json
    libtriangulation
)


include(GoogleTest)
gtest_discover_tests(MeshProcessorTests)