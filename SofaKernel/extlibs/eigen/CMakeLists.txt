cmake_minimum_required(VERSION 3.1)

# Change EIGEN_ROOT value to not use the embedded extlib
set(EIGEN_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/3.2.7" CACHE PATH "Directory for find_package(Eigen3)")

install(DIRECTORY ${EIGEN_ROOT}/Eigen
        COMPONENT Eigen_headers
        DESTINATION "include/extlibs/Eigen"
        PATTERN "*.in" EXCLUDE
        PATTERN "*.txt" EXCLUDE
        PATTERN "*.cpp" EXCLUDE)

install(DIRECTORY ${EIGEN_ROOT}/unsupported/Eigen
        COMPONENT Eigen_headers
        DESTINATION "include/extlibs/Eigen"
        PATTERN "*.in" EXCLUDE
        PATTERN "*.txt" EXCLUDE
        PATTERN "*.cpp" EXCLUDE)
