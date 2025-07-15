set(LIBRARY_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/JsonUtils.cpp"
)
set(LIBRARY_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/JsonUtils.h"
)
add_library(JsonUtils STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories(JsonUtils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(JsonUtils PUBLIC 
    nlohmann_json
    libtriangulation
    spdlog::spdlog
) 
