cmake_minimum_required(VERSION 3.1)
project(SofaModeler)

set(SOFAMODELER_MAJOR_VERSION 0)
set(SOFAMODELER_MINOR_VERSION 1)
set(SOFAMODELER_VERSION ${SOFAMODELER_MAJOR_VERSION}.${SOFAMODELER_MINOR_VERSION})

set(HEADER_FILES
    ../../../sofa/gui/qt/SofaPluginManager.h
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
    SofaModeler.h
    SofaTutorialManager.h
    TutorialSelector.h
)

set(SOURCE_FILES
    ../../../sofa/gui/qt/SofaPluginManager.cpp
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
    SofaModeler.cpp
    SofaTutorialManager.cpp
    TutorialSelector.cpp
)

set(UI_FILES ../../../sofa/gui/qt/PluginManager.ui)

find_package(Qt5 COMPONENTS Core QUIET)

if(Qt5Core_FOUND)
    message("Modeler library: Using Qt5")
    find_package(Qt5 COMPONENTS Gui OpenGL REQUIRED)

    set(EXT_QT_INCLUDES ${Qt5Core_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5OpenGL_INCLUDE_DIRS} ${Qt5Xml_INCLUDE_DIRS})
    set(EXT_QT_LIBRARIES ${Qt5Core_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5OpenGL_LIBRARIES})

    qt5_wrap_cpp(MOC_FILES ${HEADER_FILES})
    set(MOC_FILES_GROUP "Generated")

    qt5_wrap_ui(FORM_FILES ${UI_FILES})
    set(FORM_FILES_GROUP "Generated")

else()
    message("Modeler library: Using Qt4")

    find_package(Qt4 COMPONENTS qtcore qtgui qtopengl qtxml)
    set (EXT_QT_INCLUDES ${QT_INCLUDES})
    set(EXT_QT_LIBRARIES ${QT_LIBRARIES})

    qt4_wrap_cpp(MOC_FILES ${HEADER_FILES})
    set(MOC_FILES_GROUP "Generated")

    qt4_wrap_ui(FORM_FILES ${UI_FILES})
    set(FORM_FILES_GROUP "Generated")
endif()

configure_file(config.h.in "${CMAKE_BINARY_DIR}/include/SofaModeler/config.h")
install(FILES "${CMAKE_BINARY_DIR}/include/SofaModeler/config.h" DESTINATION "include/SofaModeler")

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${MOC_FILES} ${FORM_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} SofaGuiMain SofaComponentBase SofaComponentCommon SofaComponentGeneral SofaComponentAdvanced SofaComponentMisc ${EXT_QT_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${SOFAMODELER_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-DSOFA_BUILD_SOFAMODELER")
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${HEADER_FILES}")

target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${EXT_QT_INCLUDES}>")
target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/..")
target_include_directories(${PROJECT_NAME} PUBLIC "$<INSTALL_INTERFACE:include>")

sofa_create_package(SofaModeler ${SOFAMODELER_VERSION} SofaModeler SofaModeler)
