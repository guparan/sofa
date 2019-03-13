cmake_minimum_required(VERSION 3.1)
project(CGALPlugin VERSION 0.1)


set(HEADER_FILES
    DecimateMesh.h
    DecimateMesh.inl
    MeshGenerationFromPolyhedron.h
    MeshGenerationFromPolyhedron.inl
    TriangularConvexHull3D.h
    TriangularConvexHull3D.inl
    CylinderMesh.h
    CylinderMesh.inl
)

set(SOURCE_FILES
    DecimateMesh.cpp
    MeshGenerationFromPolyhedron.cpp
    TriangularConvexHull3D.cpp
    initCGALPlugin.cpp
    CylinderMesh.cpp
)

set(README_FILES CGALPlugin.txt)


### Dependencies
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(SofaFramework REQUIRED)
find_package(image QUIET)
if(image_FOUND)
    list(APPEND HEADER_FILES MeshGenerationFromImage.h)
    list(APPEND HEADER_FILES MeshGenerationFromImage.inl)
    list(APPEND SOURCE_FILES MeshGenerationFromImage.cpp)
    find_package(CGAL REQUIRED COMPONENTS ImageIO)
else()
    message(STATUS "CGALPlugin: could not find image, won't build MeshGenerationFromImage")
    find_package(CGAL REQUIRED)
endif()
## CGAL dependencies
find_package(MPFR REQUIRED)
find_package(GMP REQUIRED)
find_package(Boost QUIET REQUIRED COMPONENTS system thread)

message(STATUS "CGAL VERSION ${CGAL_MAJOR_VERSION}.${CGAL_MINOR_VERSION}")
set(CGAL_VERSION ${CGAL_MAJOR_VERSION}.${CGAL_MINOR_VERSION})
if (CGAL_VERSION VERSION_GREATER 4.9) # if CGAL >= 4.10
    add_definitions(-DCGAL_MESH_3_VERBOSE=0)
endif()


## CGALPlugin/config.h
configure_file(config.h.in "${CMAKE_BINARY_DIR}/include/CGALPlugin/config.h")
install(FILES "${CMAKE_BINARY_DIR}/include/CGALPlugin/config.h" DESTINATION "include/CGALPlugin")

if(WIN32)
    sofa_copy_libraries(${GMP_LIBRARIES} ${MPFR_LIBRARIES} ${CGAL_LIBRARIES})
    sofa_install_libraries(${GMP_LIBRARIES} ${MPFR_LIBRARIES} ${CGAL_LIBRARIES})
endif()

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES} ${README_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>")
target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>")
target_include_directories(${PROJECT_NAME} PUBLIC "$<INSTALL_INTERFACE:include>")
target_include_directories(${PROJECT_NAME} PUBLIC ${GMP_INCLUDE_DIR} ${MPFR_INCLUDE_DIR} ${CGAL_INCLUDE_DIRS})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "_d")
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-DSOFA_BUILD_CGALPLUGIN")
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${HEADER_FILES}")
target_link_libraries(${PROJECT_NAME} PUBLIC SofaCore SofaSimulationCommon ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${GMP_LIBRARIES} ${MPFR_LIBRARIES} CGAL)
if(image_FOUND)
    target_link_libraries(${PROJECT_NAME} PUBLIC image)
    target_link_libraries(${PROJECT_NAME} PUBLIC CGAL_ImageIO)
    set_target_properties(CGAL_ImageIO PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${CGAL_INCLUDE_DIRS})
endif()

if(SOFA_BUILD_TESTS)
   find_package(SofaTest QUIET)
   add_subdirectory(CGALPlugin_test)
endif()

## Install rules for the library and the headers; CMake package configurations files
sofa_generate_package(
    NAME CGALPlugin
    VERSION ${PROJECT_VERSION}
    TARGETS "${CGAL_LIBRARIES};CGALPlugin"
    INCLUDE_ROOT_DIR CGALPlugin
    )

## Install rules for the resources
install(DIRECTORY scenes/ DESTINATION share/sofa/plugins/${PROJECT_NAME})
