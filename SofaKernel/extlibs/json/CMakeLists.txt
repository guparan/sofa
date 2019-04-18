cmake_minimum_required(VERSION 3.1)

# Change JSON_ROOT value to not use the embedded extlib
set(JSON_ROOT "${CMAKE_CURRENT_SOURCE_DIR}" CACHE PATH "Nlohmann json directory")
set(JSON_INCLUDE_DIR "${JSON_ROOT}")

install(DIRECTORY ${JSON_ROOT}
    COMPONENT headers
    DESTINATION "include/extlibs"
    PATTERN "*.in" EXCLUDE
    PATTERN "*.txt" EXCLUDE
    PATTERN "*.cpp" EXCLUDE
    )
