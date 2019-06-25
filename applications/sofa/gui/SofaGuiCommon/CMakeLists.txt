cmake_minimum_required(VERSION 3.1)
project(SofaGuiCommon)

set(HEADER_FILES
    ../BaseGUI.h
    ../BaseViewer.h
    ../BatchGUI.h
    ../ColourPickingVisitor.h
    ../MouseOperations.h
    ../OperationFactory.h
    ../PickHandler.h
    ../FilesRecentlyOpenedManager.h
    ../SofaGUI.h
    ../ViewerFactory.h
    ../GUIManager.h
    ../GuiDataRepository.h
)

set(SOURCE_FILES
    ../BaseGUI.cpp
    ../BaseViewer.cpp
    ../BatchGUI.cpp
    ../ColourPickingVisitor.cpp
    ../FilesRecentlyOpenedManager.cpp
    ../MouseOperations.cpp
    ../PickHandler.cpp
    ../GUIManager.cpp
    ../ViewerFactory.cpp
    ../GuiDataRepository.cpp
)

find_package(FFMPEGexec QUIET)

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} SofaGraphComponent SofaBaseCollision SofaUserInteraction SofaBaseVisual SofaComponentBase SofaComponentCommon SofaComponentGeneral SofaComponentAdvanced SofaComponentMisc)

sofa_install_targets(SofaGui SofaGuiCommon "SofaGui/sofa/gui")
