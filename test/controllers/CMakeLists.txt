
add_library(ControllersTestSources OBJECT
    TriangulationControllerTest.cpp
    HealthControllerTest.cpp
)

target_include_directories(ControllersTestSources PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(ControllersTestSources PUBLIC
    gtest
    gmock
    TriangulationController
    HealthController
    TriangulationService
    JsonUtils
    ResponseHandler
    httplib
    spdlog::spdlog
    nlohmann_json
    libtriangulation
)

target_link_libraries(MeshProcessorTestSources INTERFACE $<TARGET_OBJECTS:ControllersTestSources>) 