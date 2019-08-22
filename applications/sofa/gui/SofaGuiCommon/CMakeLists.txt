cmake_minimum_required(VERSION 3.1)
project(SofaGuiCommon)

find_package(SofaGeneral REQUIRED)
find_package(Boost COMPONENTS program_options)

set(HEADER_FILES
    ../BaseGUI.h
    ../BaseViewer.h
    ../BatchGUI.h
    ../ColourPickingVisitor.h
    ../FilesRecentlyOpenedManager.h
    ../GuiDataRepository.h
    ../GUIManager.h
    ../MouseOperations.h
    ../OperationFactory.h
    ../PickHandler.h
    ../SofaGUI.h
    ../ViewerFactory.h
)

set(SOURCE_FILES
    ../BaseGUI.cpp
    ../BaseViewer.cpp
    ../BatchGUI.cpp
    ../ColourPickingVisitor.cpp
    ../FilesRecentlyOpenedManager.cpp
    ../GuiDataRepository.cpp
    ../GUIManager.cpp
    ../MouseOperations.cpp
    ../PickHandler.cpp
    ../ViewerFactory.cpp
)

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC
    SofaHelper SofaGraphComponent SofaBaseCollision SofaUserInteraction SofaBaseVisual
    SofaComponentBase SofaComponentCommon SofaComponentGeneral SofaComponentAdvanced SofaComponentMisc
    )
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::program_options)
if(NOT SOFA_NO_OPENGL)
    find_package(OpenGL)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})
    find_package(GLEW)
    target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-DSOFA_BUILD_SOFAGUI")
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${HEADER_FILES}")

sofa_install_targets(SofaGui SofaGuiCommon "SofaGui/sofa/gui")
