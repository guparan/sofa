cmake_minimum_required(VERSION 3.1)
project(Tutorials)

if(APPLE)
    set(RC_FILES "../Modeler.icns")
else()
    set(RC_FILES "sofa.rc")
endif()

set(HEADER_FILES
    ../../sofa/gui/qt/SofaPluginManager.h
    AddPreset.h
    FilterLibrary.h
    GlobalModification.h
    GraphHistoryManager.h
    GraphModeler.h
    LinkComponent.h
    ModifierCondition.h
    QCategoryTreeLibrary.h
    QComponentTreeLibrary.h
    QSofaTreeLibrary.h
    SofaTutorials.h
    SofaTutorialsManager.h
    TutorialSelector.h
)

set(SOURCE_FILES
    ../../sofa/gui/qt/SofaPluginManager.cpp
    AddPreset.cpp
    FilterLibrary.cpp
    GlobalModification.cpp
    GraphHistoryManager.cpp
    GraphModeler.cpp
    LinkComponent.cpp
    ModifierCondition.cpp
    QCategoryTreeLibrary.cpp
    QComponentTreeLibrary.cpp
    QSofaTreeLibrary.cpp
    SofaTutorials.cpp
    SofaTutorialsManager.cpp
    TutorialSelector.cpp
)

set(UI_FILES ../../sofa/gui/qt/PluginManager.ui)

find_package(Qt5 COMPONENTS Core QUIET)

if(Qt5Core_FOUND)
    message("Tutorials library: Using Qt5")
    find_package(Qt5 COMPONENTS Gui Widgets OpenGL REQUIRED)
    qt5_add_resources(RESOURCE_FILES "${CMAKE_SOURCE_DIR}/share/textures/modeler/icons.qrc")

    set(EXT_QT_INCLUDES ${Qt5Core_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5OpenGL_INCLUDE_DIRS} ${Qt5Xml_INCLUDE_DIRS})
    set(EXT_QT_LIBRARIES ${Qt5Core_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5OpenGL_LIBRARIES})

    qt5_wrap_cpp(MOC_FILES ${HEADER_FILES})
    set(MOC_FILES_GROUP "Generated")

    qt5_wrap_ui(FORM_FILES ${UI_FILES})
    set(FORM_FILES_GROUP "Generated")

else()
    message("Tutorials library: Using Qt4")
    find_package(Qt4 COMPONENTS qtcore qtgui qtopengl qtxml)
	qt4_add_resources(RESOURCE_FILES "${CMAKE_SOURCE_DIR}/share/textures/modeler/icons.qrc")
    
    set(EXT_QT_INCLUDES ${QT_INCLUDES})
    set(EXT_QT_LIBRARIES ${QT_LIBRARIES})

    qt4_wrap_cpp(MOC_FILES ${HEADER_FILES})
    set(MOC_FILES_GROUP "Generated")

    qt4_wrap_ui(FORM_FILES ${UI_FILES})
    set(FORM_FILES_GROUP "Generated")
endif()

add_library("lib${PROJECT_NAME}" STATIC ${HEADER_FILES} ${MOC_FILES} ${FORM_FILES} ${SOURCE_FILES})
target_link_libraries("lib${PROJECT_NAME}" SofaGuiMain SofaComponentBase SofaComponentCommon SofaComponentGeneral SofaComponentAdvanced SofaComponentMisc ${EXT_QT_LIBRARIES})
set_target_properties("lib${PROJECT_NAME}" PROPERTIES PUBLIC_HEADER "${HEADER_FILES}")
target_include_directories("lib${PROJECT_NAME}" PUBLIC "$<BUILD_INTERFACE:${EXT_QT_INCLUDES}>")

add_executable(${PROJECT_NAME} Main.cpp ${RC_FILES} ${RESOURCE_FILES})
target_link_libraries(${PROJECT_NAME} "lib${PROJECT_NAME}" SofaComponentBase SofaComponentCommon SofaComponentGeneral SofaComponentAdvanced SofaComponentMisc ${EXT_QT_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${HEADER_FILES}")
target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${EXT_QT_INCLUDES}>")

sofa_install_targets(SofaGui Tutorials "")
