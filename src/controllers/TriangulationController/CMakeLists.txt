set(LIBRARY_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/TriangulationController.cpp"
)
set(LIBRARY_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/TriangulationController.h"
)

add_library(TriangulationController STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories(TriangulationController PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(TriangulationController PUBLIC 
    TriangulationService 
    JsonUtils 
    ResponseHandler
    ControllerInterfaces
    spdlog::spdlog
) 