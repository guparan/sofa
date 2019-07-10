cmake_minimum_required(VERSION 3.1)
project(SofaSimulationGraph)

set(HEADER_FILES
    DAGNode.h
    DAGNodeMultiMappingElement.h
    DAGSimulation.h
    SimpleApi.h
    init.h
    graph.h
)

set(SOURCE_FILES
    DAGNode.cpp
    DAGNodeMultiMappingElement.cpp
    DAGSimulation.cpp
    SimpleApi.cpp
    init.cpp
)

if(SOFA_BUILD_TESTS)
    list(APPEND HEADER_FILES testing/BaseSimulationTest.h)
    list(APPEND SOURCE_FILES testing/BaseSimulationTest.cpp)
endif()

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC SofaSimulationCommon)
target_compile_definitions(${PROJECT_NAME} PUBLIC "-DSOFA_HAVE_DAG")

sofa_install_targets(SofaSimulation ${PROJECT_NAME} "SofaSimulation/${PROJECT_NAME}")

if (SOFA_BUILD_TESTS)
    add_subdirectory(SofaSimulationGraph_test)
endif (SOFA_BUILD_TESTS)
