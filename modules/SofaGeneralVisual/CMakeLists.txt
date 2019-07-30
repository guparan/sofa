cmake_minimum_required(VERSION 3.1)
project(SofaGeneralVisual)

set(HEADER_FILES
    config.h
    initGeneralVisual.h
    )

set(SOURCE_FILES
    initGeneralVisual.cpp
    )

list(APPEND HEADER_FILES
    RecordedCamera.h
    VisualTransform.h
    Visual3DText.h
    )
list(APPEND SOURCE_FILES
    RecordedCamera.cpp
    VisualTransform.cpp
    Visual3DText.cpp
    )

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC SofaBaseTopology SofaBaseVisual)
if(NOT SOFA_NO_OPENGL)
    find_package(OpenGL)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-DSOFA_BUILD_GENERAL_VISUAL")
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${HEADER_FILES}")

sofa_install_targets(SofaGeneral ${PROJECT_NAME} "SofaGeneral/${PROJECT_NAME}")
