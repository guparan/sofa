cmake_minimum_required(VERSION 3.1)
project(SofaGuiMain)

set(HEADER_FILES
    ../Main.h
)

set(SOURCE_FILES
    ../Main.cpp
)

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})
if(TARGET SofaGuiQt)
    target_link_libraries(${PROJECT_NAME} PUBLIC SofaGuiQt)
endif()
if(TARGET SofaGuiCommon)
    target_link_libraries(${PROJECT_NAME} PUBLIC SofaGuiCommon)
endif()
if(TARGET SofaHeadlessRecorder)
    target_link_libraries(${PROJECT_NAME} PUBLIC SofaHeadlessRecorder)
endif()
find_package(Boost COMPONENTS program_options)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::program_options)
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-DSOFA_BUILD_GUIMAIN")
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${HEADER_FILES}")

sofa_install_targets(SofaGui SofaGuiMain "SofaGui/sofa/gui")
