cmake_minimum_required(VERSION 3.1)
project(SofaComponentAll)

set(SOFACOMPONENTALL_VERSION 1.0)

find_package(SofaBase REQUIRED)
find_package(SofaCommon REQUIRED)
find_package(SofaGeneral REQUIRED)
find_package(SofaAdvanced REQUIRED)
find_package(SofaMisc REQUIRED)

set(HEADER_FILES
    config.h
    initComponentAll.h
)

set(SOURCE_FILES
    initComponentAll.cpp
)

set(EXTRA_FILES
    README.md
    )

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES} ${EXTRA_FILES})
target_link_libraries(${PROJECT_NAME} SofaComponentBase SofaComponentCommon SofaComponentGeneral SofaComponentAdvanced SofaComponentMisc)
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-DSOFA_BUILD_SOFACOMPONENTALL -DSOFA_SRC_DIR=\"${CMAKE_SOURCE_DIR}\"")
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${HEADER_FILES}")
target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>")
target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>")

sofa_create_package(${PROJECT_NAME} "1.0" ${PROJECT_NAME} ${PROJECT_NAME})
