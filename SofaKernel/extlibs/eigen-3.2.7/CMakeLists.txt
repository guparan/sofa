cmake_minimum_required(VERSION 3.1)
#project(Eigen3 VERSION 3.2.7)

# Use embedded headers by default (change EIGEN_ROOT to use another Eigen)
set(EIGEN_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/3.2.7" CACHE PATH "Eigen root containing Eigen/src/...")

find_package(Eigen3 REQUIRED)

# TODO: create a proper Eigen target
#add_library(Eigen3 INTERFACE)
#target_include_directories(Eigen3 INTERFACE
#    $<BUILD_INTERFACE:${EIGEN_ROOT}/Eigen>
#    $<INSTALL_INTERFACE:include/Eigen>
#    )
#include_directories("$<INSTALL_INTERFACE:include/Eigen>")

#install(TARGETS Eigen3
#        EXPORT Eigen3Targets)

if(EIGEN3_FOUND OR Eigen3_FOUND)
    if(NOT EIGEN3_INCLUDE_DIR) # should be created by find_package(Eigen3)
        set(EIGEN3_INCLUDE_DIR ${EIGEN_ROOT})
    endif()

    install(DIRECTORY ${EIGEN3_INCLUDE_DIR}/Eigen
            COMPONENT headers
            DESTINATION "include/extlibs/Eigen"
            PATTERN "*.in" EXCLUDE
            PATTERN "*.txt" EXCLUDE
            PATTERN "*.cpp" EXCLUDE)

    install(DIRECTORY ${EIGEN3_INCLUDE_DIR}/unsupported/Eigen
            COMPONENT headers
            DESTINATION "include/extlibs/Eigen"
            PATTERN "*.in" EXCLUDE
            PATTERN "*.txt" EXCLUDE
            PATTERN "*.cpp" EXCLUDE)
else()
    message(SEND_ERROR "-- Eigen not found. Set EIGEN_ROOT to a correct Eigen directory.")
endif()

#include(../../SofaFramework/SofaMacros.cmake)
#sofa_write_package_config_files(${PROJECT_NAME} ${PROJECT_VERSION})
