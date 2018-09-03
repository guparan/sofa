cmake_minimum_required(VERSION 3.1)

project(Sofa.Component.SolidMechanics.Fem VERSION 1.0)

find_package(SofaBase)
find_package(SofaCommon)
find_package(SofaGeneral)

set(HEADER_FILES config/${PROJECT_NAME}.h)
set(SOURCE_FILES config/${PROJECT_NAME}.cpp)

list(APPEND HEADER_FILES
    deprecated_layout/SofaGeneralSimpleFem/BeamFEMForceField.h
)

list(APPEND HEADER_FILES
    src/sofa/component/solidmechanics/fem/BeamFEMForceField.h
    src/sofa/component/solidmechanics/fem/BeamFEMForceField.inl
)
list(APPEND SOURCE_FILES
    src/sofa/component/solidmechanics/fem/BeamFEMForceField.cpp
)

set(EXTRA_FILES
)

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES} ${EXTRA_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC SofaBaseTopology SofaGeneralSimpleFem SofaSimpleFem)
target_compile_definitions(${PROJECT_NAME} PRIVATE "-DBUILD_SOFA_COMPONENT_SOLIDMECHANICS_FEM")
target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/config>")
target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/deprecated_layout>")
target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>")

sofa_create_package(${PROJECT_NAME} ${PROJECT_VERSION} ${PROJECT_NAME} ${PROJECT_NAME})
