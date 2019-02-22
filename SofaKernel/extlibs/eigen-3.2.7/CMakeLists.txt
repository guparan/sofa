cmake_minimum_required(VERSION 3.1)
#project(Eigen3 VERSION 3.2.7)

set(EIGEN_ROOT "${CMAKE_CURRENT_SOURCE_DIR}" CACHE PATH "Directory for find_package(Eigen3)")
set(EIGEN3_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" CACHE PATH "Include directory for find_package(Eigen3)")

#add_library(Eigen3 INTERFACE)
#target_include_directories(Eigen3 INTERFACE
#    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Eigen>
#    $<INSTALL_INTERFACE:include/Eigen>
#)
#include_directories("$<INSTALL_INTERFACE:include/Eigen>")

#install(TARGETS Eigen3
#        EXPORT Eigen3Targets)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Eigen
        COMPONENT Eigen_headers
        DESTINATION include/Eigen
        PATTERN "*.in" EXCLUDE
        PATTERN "*.txt" EXCLUDE
        PATTERN "*.cpp" EXCLUDE)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/unsupported/Eigen
        COMPONENT Eigen_headers
        DESTINATION include/Eigen
        PATTERN "*.in" EXCLUDE
        PATTERN "*.txt" EXCLUDE
        PATTERN "*.cpp" EXCLUDE)

#include(../../SofaFramework/SofaMacros.cmake)
#sofa_write_package_config_files(${PROJECT_NAME} ${PROJECT_VERSION})
