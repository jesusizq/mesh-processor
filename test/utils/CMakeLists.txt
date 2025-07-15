add_library(UtilsTestSources OBJECT
    JsonUtilsTest.cpp
)

target_include_directories(UtilsTestSources PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(UtilsTestSources PUBLIC
    gtest
    gmock
    JsonUtils
    nlohmann_json
    libtriangulation
)

target_link_libraries(MeshProcessorTestSources INTERFACE $<TARGET_OBJECTS:UtilsTestSources>) 