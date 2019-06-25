cmake_minimum_required(VERSION 3.1)
project(SofaMisc)

set(HEADER_FILES
    initMisc.h
    )

set(SOURCE_FILES
    initMisc.cpp
    )

list(APPEND HEADER_FILES
    MeshTetraStuffing.h
    AddResourceRepository.h
    )
list(APPEND SOURCE_FILES
    MeshTetraStuffing.cpp
    AddResourceRepository.cpp
    )

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC SofaGeneralMeshCollision SofaMiscTopology SofaTopologyMapping)

sofa_install_targets(SofaMisc ${PROJECT_NAME} "SofaMisc/${PROJECT_NAME}")
