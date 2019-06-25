cmake_minimum_required(VERSION 3.1)
project(SofaBaseVisual)

set(HEADER_FILES
    BaseCamera.h
    BackgroundSetting.h
    Camera.h
    InteractiveCamera.h
    VisualModelImpl.h
    VisualStyle.h
    initBaseVisual.h
)

set(SOURCE_FILES
    BaseCamera.cpp
    BackgroundSetting.cpp
    Camera.cpp
    InteractiveCamera.cpp
    VisualModelImpl.cpp
    VisualStyle.cpp
    initBaseVisual.cpp
)

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC SofaBaseTopology)

sofa_install_targets(SofaBase ${PROJECT_NAME} "SofaBase/${PROJECT_NAME}")
