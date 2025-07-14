cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(MeshProcessor VERSION 1.0.0 LANGUAGES CXX)

add_subdirectory(libs)
add_subdirectory(src)
add_subdirectory(app)

target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog httplib::httplib nlohmann_json libtriangulation)

# INSTALL TARGETS
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

