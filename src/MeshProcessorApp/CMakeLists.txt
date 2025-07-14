set(LIBRARY_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/MeshProcessorApp.cpp"
)
set(LIBRARY_HEADERS 
    "${CMAKE_CURRENT_SOURCE_DIR}/MeshProcessorApp.h"
)

add_library(MeshProcessorApp STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories(MeshProcessorApp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(MeshProcessorApp PRIVATE ApiResponse spdlog::spdlog httplib::httplib nlohmann_json libtriangulation)
