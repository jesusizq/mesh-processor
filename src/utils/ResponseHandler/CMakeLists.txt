set(LIBRARY_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/ResponseHandler.cpp"
)
set(LIBRARY_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/ResponseHandler.h"
)

add_library(ResponseHandler STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories(ResponseHandler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ResponseHandler PUBLIC httplib nlohmann_json)