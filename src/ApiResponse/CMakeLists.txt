set(LIBRARY_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/ApiResponse.cpp"
)
set(LIBRARY_HEADERS 
    "${CMAKE_CURRENT_SOURCE_DIR}/ApiResponse.h"
)

add_library(ApiResponse STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories(ApiResponse PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ApiResponse PUBLIC nlohmann_json)
