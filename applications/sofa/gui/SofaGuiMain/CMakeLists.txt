cmake_minimum_required(VERSION 3.1)
project(SofaGuiMain)

set(HEADER_FILES
    ../Main.h
)

set(SOURCE_FILES
    ../Main.cpp
)

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})
set(SOFAGUIMAIN_DEPS ${SOFAGUI_TARGETS})
list(REMOVE_ITEM SOFAGUIMAIN_DEPS SofaGuiMain)
target_link_libraries(${PROJECT_NAME} ${SOFAGUIMAIN_DEPS})

sofa_install_targets(SofaGui SofaGuiMain "SofaGui/sofa/gui")
