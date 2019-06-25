cmake_minimum_required(VERSION 3.1)
project(SofaDenseSolver)

set(HEADER_FILES
    initDenseSolver.h
    )

set(SOURCE_FILES
    initDenseSolver.cpp
    )

list(APPEND HEADER_FILES
    LULinearSolver.h
    NewMatMatrix.h
    NewMatVector.h
    )
list(APPEND SOURCE_FILES
    LULinearSolver.cpp
    NewMatCGLinearSolver.cpp
    NewMatCholeskySolver.cpp
    )

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC SofaBaseLinearSolver)
target_link_libraries(${PROJECT_NAME} PUBLIC newmat)

sofa_install_targets(SofaGeneral ${PROJECT_NAME} "SofaGeneral/${PROJECT_NAME}")
