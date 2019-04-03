cmake_minimum_required(VERSION 3.1)

set(EXTLIBS_TARGETS
    csparse
)

## Necessary ones
#find_package(SuiteSparse QUIET)
#message("SuiteSparse_FOUND = ${SuiteSparse_FOUND}")
#if(NOT SuiteSparse_FOUND)
#    add_subdirectory(SuiteSparse)
#endif()

find_package(CSparse QUIET)
if(NOT CSparse_FOUND)
    add_subdirectory(csparse)
endif()

if(SOFAGUI_ENABLE_QWT)
    message("Qwt activated")
    add_subdirectory(qwt-6.1.2/src qwt)
    list(APPEND EXTLIBS_TARGETS qwt)
endif()

option(SOFA_BUILD_MINIFLOWVR "Build the miniFlowVR library distributed in the extlibs/ directory." OFF)
if(SOFA_BUILD_MINIFLOWVR)
    add_subdirectory(miniFlowVR)
    list(APPEND EXTLIBS_TARGETS miniFlowVR)
endif()

option(SOFA_BUILD_ARTRACK
"Build the ARTrack library distributed in the extlibs/ directory.  This library
is used only by the ARTrack plugin."  OFF)
if(SOFA_BUILD_ARTRACK)
    add_subdirectory(ARTrack ARTrackLib)
    list(APPEND EXTLIBS_TARGETS ARTrackLib)
endif()

option(SOFA_BUILD_METIS
"Build the metis library distributed in the extlibs/ directory.  It is used only
by the SparseLDLSolver component.  Note that this library is usually available
on Linux distributions." OFF)
if(SOFA_BUILD_METIS)
    add_subdirectory(metis-5.1.0 "metis")
    list(APPEND EXTLIBS_TARGETS metis)
endif()

foreach(target ${EXTLIBS_TARGETS})
    set_target_properties(${target} PROPERTIES DEBUG_POSTFIX "_d")
    set_target_properties(${target} PROPERTIES FOLDER "SofaExtlibs")
endforeach()

