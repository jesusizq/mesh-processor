add_subdirectory(libtriangulation)
add_subdirectory(spdlog)
add_subdirectory(httplib)

# libtriangulation might have already created the nlohmann_json target via FetchContent.
# Only add the nlohmann subdirectory if the target doesn't already exist.
if(NOT TARGET nlohmann_json)
    add_subdirectory(nlohmann)
endif()