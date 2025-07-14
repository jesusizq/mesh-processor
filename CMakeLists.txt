cmake_minimum_required(VERSION 3.15)

if(NOT PROJECT_VERSION)
  set(PROJECT_VERSION 0.0.1)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(MeshProcessor VERSION ${PROJECT_VERSION} LANGUAGES CXX)

message(STATUS "Project: ${PROJECT_NAME} Version: ${PROJECT_VERSION}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

# Global options
option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" ON)
option(BUILD_TESTING "Enable test builds" OFF)

# Add subdirectories for external libs, the app, and source code
add_subdirectory(libs)
add_subdirectory(src)
add_subdirectory(app)

target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog httplib::httplib nlohmann_json libtriangulation)

# INSTALL TARGETS
install(TARGETS ${PROJECT_NAME} DESTINATION bin)



