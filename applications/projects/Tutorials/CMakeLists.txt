cmake_minimum_required(VERSION 3.1)
project(Tutorials)

if(APPLE)
    set(RC_FILES "../Modeler.icns")
else()
    set(RC_FILES "sofa.rc")
endif()

set(HEADER_FILES
    Tutorials.h
)

set(SOURCE_FILES
    Tutorials.cpp
)

find_package(SofaModeler REQUIRED)
find_package(Qt5 COMPONENTS Core QUIET)

if(Qt5Core_FOUND)
    message("Tutorials library: Using Qt5")
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    qt5_add_resources(RESOURCE_FILES "${CMAKE_SOURCE_DIR}/share/textures/modeler/icons.qrc")

    set(EXT_QT_INCLUDES ${Qt5Core_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})
    set(EXT_QT_LIBRARIES ${Qt5Core_LIBRARIES} ${Qt5Widgets_LIBRARIES})

    qt5_wrap_cpp(MOC_FILES ${HEADER_FILES})
    set(MOC_FILES_GROUP "Generated")
    qt5_wrap_ui(FORM_FILES ${UI_FILES})
    set(FORM_FILES_GROUP "Generated")
else()
    message("Tutorials library: Using Qt4")
    find_package(Qt4 COMPONENTS qtcore qtwidgets REQUIRED)
    qt4_add_resources(RESOURCE_FILES "${CMAKE_SOURCE_DIR}/share/textures/modeler/icons.qrc")

    set(EXT_QT_INCLUDES ${QT_INCLUDES})
    set(EXT_QT_LIBRARIES ${QT_LIBRARIES})

    qt4_wrap_cpp(MOC_FILES ${HEADER_FILES})
    set(MOC_FILES_GROUP "Generated")
    qt4_wrap_ui(FORM_FILES ${UI_FILES})
    set(FORM_FILES_GROUP "Generated")
endif()

add_executable(${PROJECT_NAME} Main.cpp ${HEADER_FILES} ${MOC_FILES} ${FORM_FILES} ${SOURCE_FILES} ${RC_FILES} ${RESOURCE_FILES})
target_link_libraries(${PROJECT_NAME} SofaModeler)

sofa_install_targets(SofaGui Tutorials "")
