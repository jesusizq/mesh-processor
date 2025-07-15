add_library(ControllerInterfaces INTERFACE)

target_include_directories(ControllerInterfaces INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ControllerInterfaces INTERFACE httplib)
add_subdirectory(TriangulationController) 