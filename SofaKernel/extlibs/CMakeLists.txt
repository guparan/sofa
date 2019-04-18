cmake_minimum_required(VERSION 3.1)

set(EXTLIBS_TARGETS
    newmat
    tinyxml
)

# Eigen (header-only)
set(EIGEN_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/eigen-3.2.7" CACHE PATH "Eigen directory (containing Eigen/src/...)")
mark_as_advanced(EIGEN_ROOT)

# Newmat
find_package(Newmat QUIET)
if(NOT Newmat_FOUND)
    add_subdirectory(newmat)
endif()

# TinyXML
find_package(TinyXML QUIET)
if(NOT TinyXML_FOUND)
    add_subdirectory(tinyxml)
endif()

# Nlohmann JSON (header-only)
set(JSON_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/json" CACHE PATH "Nlohmann JSON directory")
mark_as_advanced(JSON_ROOT)

foreach(target ${EXTLIBS_TARGETS})
    set_target_properties(${target} PROPERTIES DEBUG_POSTFIX "_d")
    set_target_properties(${target} PROPERTIES FOLDER "SofaExtlibs")
endforeach()

# C++11
set(CPP11_EXTLIBS_TARGETS ${EXTLIBS_TARGETS})
if(NOT WIN32)
    if(SOFA_USE_C++11)
        foreach(target ${CPP11_EXTLIBS_TARGETS})
            target_compile_options(${target} PRIVATE "$<$<STREQUAL:$<TARGET_PROPERTY:LINKER_LANGUAGE>,CXX>:${CXX11_FLAG}>")
            if ("${CMAKE_CXX_COMPILER} ${CMAKE_CXX_COMPILER_ARG1}" MATCHES ".*clang") # Wno-deprecated-register does not exist in GCC
                target_compile_options(${target} PRIVATE "$<$<STREQUAL:$<TARGET_PROPERTY:LINKER_LANGUAGE>,CXX>:-Wno-deprecated-register>")
            endif()
        endforeach()
    endif()
endif()
