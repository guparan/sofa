cmake_minimum_required(VERSION 3.1)
project(SofaMiscEngine)

set(HEADER_FILES
    initMiscEngine.h
    )

set(SOURCE_FILES
    initMiscEngine.cpp
    )

list(APPEND HEADER_FILES
    DisplacementMatrixEngine.h
    DisplacementMatrixEngine.inl
    Distances.h
    Distances.inl
    ProjectiveTransformEngine.h
    ProjectiveTransformEngine.inl
    )
list(APPEND SOURCE_FILES
    DisplacementMatrixEngine.cpp
    Distances.cpp
    ProjectiveTransformEngine.cpp
    )

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC SofaNonUniformFem)

sofa_install_targets(SofaMisc ${PROJECT_NAME} "SofaMisc/${PROJECT_NAME}")
