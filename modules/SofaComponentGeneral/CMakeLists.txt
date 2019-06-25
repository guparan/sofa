cmake_minimum_required(VERSION 3.1)
project(SofaComponentGeneral)

set(HEADER_FILES
    initComponentGeneral.h
    )

set(SOURCE_FILES
    initComponentGeneral.cpp
    )

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC
    SofaGeneralAnimationLoop SofaGeneralDeformable SofaGeneralExplicitOdeSolver SofaGeneralImplicitOdeSolver SofaGeneralLinearSolver SofaGeneralLoader
    SofaGeneralMeshCollision SofaGeneralObjectInteraction SofaGeneralRigid SofaGeneralSimpleFem SofaGeneralTopology  SofaGeneralVisual SofaBoundaryCondition
    SofaConstraint SofaGeneralEngine SofaGraphComponent SofaTopologyMapping SofaUserInteraction SofaValidation)

if(SOFA_HAVE_NEWMAT)
    target_link_libraries(${PROJECT_NAME} PUBLIC SofaDenseSolver)
endif()

sofa_install_targets(SofaGeneral ${PROJECT_NAME} "SofaGeneral/${PROJECT_NAME}")
