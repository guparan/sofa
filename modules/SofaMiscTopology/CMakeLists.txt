cmake_minimum_required(VERSION 3.1)
project(SofaMiscTopology)

set(HEADER_FILES
initMiscTopology.h
)

set(SOURCE_FILES
initMiscTopology.cpp
)

list(APPEND HEADER_FILES
TopologicalChangeProcessor.h
)
list(APPEND SOURCE_FILES
TopologicalChangeProcessor.cpp
)

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC SofaBaseTopology)

sofa_install_targets(SofaMisc ${PROJECT_NAME} "SofaMisc/${PROJECT_NAME}")
