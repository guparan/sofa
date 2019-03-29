cmake_minimum_required(VERSION 3.1)
project(newmat)

# Change NEWMAT_ROOT value to not use the embedded extlib
set(NEWMAT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/newmat" CACHE PATH "Directory for find_package(Newmat)")

set(HEADER_FILES
    ${NEWMAT_ROOT}/boolean.h
    ${NEWMAT_ROOT}/controlw.h
    ${NEWMAT_ROOT}/include.h
    ${NEWMAT_ROOT}/myexcept.h
    ${NEWMAT_ROOT}/newmat.h
    ${NEWMAT_ROOT}/newmatap.h
    ${NEWMAT_ROOT}/newmatrc.h
    ${NEWMAT_ROOT}/newmatrm.h
    ${NEWMAT_ROOT}/precisio.h
)

set(SOURCE_FILES
    ${NEWMAT_ROOT}/bandmat.cpp
    ${NEWMAT_ROOT}/cholesky.cpp
    ${NEWMAT_ROOT}/evalue.cpp
    ${NEWMAT_ROOT}/fft.cpp
    ${NEWMAT_ROOT}/hholder.cpp
    ${NEWMAT_ROOT}/jacobi.cpp
    ${NEWMAT_ROOT}/myexcept.cpp
    ${NEWMAT_ROOT}/newfft.cpp
    ${NEWMAT_ROOT}/newmat1.cpp
    ${NEWMAT_ROOT}/newmat2.cpp
    ${NEWMAT_ROOT}/newmat3.cpp
    ${NEWMAT_ROOT}/newmat4.cpp
    ${NEWMAT_ROOT}/newmat5.cpp
    ${NEWMAT_ROOT}/newmat6.cpp
    ${NEWMAT_ROOT}/newmat7.cpp
    ${NEWMAT_ROOT}/newmat8.cpp
    ${NEWMAT_ROOT}/newmat9.cpp
    ${NEWMAT_ROOT}/newmatex.cpp
    ${NEWMAT_ROOT}/newmatrm.cpp
    ${NEWMAT_ROOT}/sort.cpp
    ${NEWMAT_ROOT}/submat.cpp
    ${NEWMAT_ROOT}/svd.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
target_include_directories(${PROJECT_NAME} PUBLIC "$<INSTALL_INTERFACE:include/extlibs/Newmat>")
target_compile_definitions(${PROJECT_NAME} PUBLIC "use_namespace")
if(NOT DEFINED SOFA_WITH_DOUBLE)
    target_compile_definitions(${PROJECT_NAME} PUBLIC "USING_FLOAT")
else()
    target_compile_definitions(${PROJECT_NAME} PUBLIC "USING_DOUBLE")
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${HEADER_FILES}")

# The code must be relocatable if we want to link a shared library against it
if("x${CMAKE_CXX_COMPILER_ID}" STREQUAL "xGNU" OR "x${CMAKE_CXX_COMPILER_ID}" STREQUAL "xClang")
    target_compile_options(${PROJECT_NAME} PRIVATE "-fPIC")
endif()


include(../../SofaFramework/SofaMacros.cmake)
sofa_generate_package(NAME Newmat VERSION 0.1 TARGETS ${PROJECT_NAME} INCLUDE_SOURCE_DIR "${NEWMAT_ROOT}" INCLUDE_INSTALL_DIR "extlibs/Newmat/newmat")
