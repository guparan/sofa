cmake_minimum_required(VERSION 3.1)
project(SofaComponentAdvanced)

set(HEADER_FILES
    initComponentAdvanced.h
)

set(SOURCE_FILES
    initComponentAdvanced.cpp
)

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC SofaNonUniformFem)

sofa_install_targets(SofaAdvanced ${PROJECT_NAME} "SofaAdvanced/${PROJECT_NAME}")
