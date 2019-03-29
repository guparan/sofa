cmake_minimum_required(VERSION 3.1)
project(tinyxml)

# Change TINYXML_ROOT value to not use the embedded extlib
set(TINYXML_ROOT "${CMAKE_CURRENT_SOURCE_DIR}" CACHE PATH "Directory containing TinyXML headers")

if("TINYXML_ROOT" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
    set(TINYXML_VERSION 2.6.2)
else()
    set(TINYXML_VERSION 0.1)
endif()

set(SOURCE_FILES
    ${TINYXML_ROOT}/tinystr.cpp
    ${TINYXML_ROOT}/tinyxml.cpp
    ${TINYXML_ROOT}/tinyxmlerror.cpp
    ${TINYXML_ROOT}/tinyxmlparser.cpp
)

set(HEADER_FILES
    ${TINYXML_ROOT}/tinystr.h
    ${TINYXML_ROOT}/tinyxml.h
)


add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
target_include_directories(${PROJECT_NAME} PUBLIC "$<INSTALL_INTERFACE:include/extlibs/TinyXML>")
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${TINYXML_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${HEADER_FILES}")

include(${SOFA_KERNEL_SOURCE_DIR}/SofaFramework/SofaMacros.cmake)
sofa_generate_package(NAME TinyXML VERSION ${TINYXML_VERSION} TARGETS ${PROJECT_NAME} INCLUDE_SOURCE_DIR "${TINYXML_ROOT}" INCLUDE_INSTALL_DIR "extlibs/TinyXML/tinyxml")
