set(LIBRARY_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/HealthController.cpp"
)
set(LIBRARY_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/HealthController.h"
)

add_library(HealthController STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories(HealthController PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(HealthController PUBLIC 
    ResponseHandler
    ControllerInterfaces
    spdlog::spdlog
    nlohmann_json
) 