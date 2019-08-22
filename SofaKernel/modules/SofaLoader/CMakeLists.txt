cmake_minimum_required(VERSION 3.1)
project(SofaLoader)

find_package(TinyXML REQUIRED)

set(HEADER_FILES
    BaseVTKReader.h
    BaseVTKReader.inl
    MeshObjLoader.h
    MeshVTKLoader.h
    config.h
    initLoader.h
)

set(SOURCE_FILES
    BaseVTKReader.cpp
    BaseVTKReader.inl
    MeshObjLoader.cpp
    MeshVTKLoader.cpp
    initLoader.cpp
)

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC SofaSimulationTree SofaHelper)
target_link_libraries(${PROJECT_NAME} PRIVATE tinyxml)
## Forwarding include dirs of privately-linked external library
#get_target_property(extlib_include_dirs tinyxml INCLUDE_DIRECTORIES)
#target_include_directories(${PROJECT_NAME} PUBLIC ${extlib_include_dirs})
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-DSOFA_BUILD_LOADER")
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${HEADER_FILES}")

sofa_install_targets(SofaCommon ${PROJECT_NAME} "SofaCommon/${PROJECT_NAME}")
