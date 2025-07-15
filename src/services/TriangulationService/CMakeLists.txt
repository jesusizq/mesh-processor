set(LIBRARY_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/TriangulationService.cpp"
)
set(LIBRARY_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/TriangulationService.h"
)

add_library(TriangulationService STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories(TriangulationService PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(TriangulationService PUBLIC libtriangulation)