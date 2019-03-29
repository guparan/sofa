cmake_minimum_required(VERSION 3.1)

set(EXTLIBS_TARGETS
    csparse
    newmat
    tinyxml
)

## Necessary ones
find_package(SuiteSparse QUIET)
message("SuiteSparse_FOUND = ${SuiteSparse_FOUND}")
if(NOT SuiteSparse_FOUND)
    add_subdirectory(SuiteSparse)
endif()

find_package(CSparse QUIET)
message("CSparse_FOUND = ${CSparse_FOUND}")
if(NOT CSparse_FOUND)
    add_subdirectory(csparse)
endif()

#message("EIGEN3_FOUND = ${EIGEN3_FOUND}")
#message("EIGEN3_INCLUDE_DIR = ${EIGEN3_INCLUDE_DIR}")
#message("EIGEN3_VERSION = ${EIGEN3_VERSION}")

#find_package(Eigen3 QUIET)
#if(NOT Eigen3_FOUND AND NOT EIGEN3_FOUND)
    add_subdirectory(${SOFA_KERNEL_SOURCE_DIR}/extlibs/eigen eigen)
#endif()

#message("EIGEN3_INCLUDE_DIR = ${EIGEN3_INCLUDE_DIR}")
#message("EIGEN3_VERSION = ${EIGEN3_VERSION}")


find_package(Newmat QUIET)
message("Newmat_FOUND = ${Newmat_FOUND}")
if(NOT Newmat_FOUND)
    add_subdirectory(${SOFA_KERNEL_SOURCE_DIR}/extlibs/newmat newmat)
endif()

find_package(TinyXML QUIET)
message("TinyXML_FOUND = ${TinyXML_FOUND}")
if(NOT TinyXML_FOUND)
    add_subdirectory(${SOFA_KERNEL_SOURCE_DIR}/extlibs/tinyxml tinyxml)
endif()

find_package(json QUIET)
message("json_FOUND = ${json_FOUND}")
if(NOT json_FOUND)
    add_subdirectory(${SOFA_KERNEL_SOURCE_DIR}/extlibs/json json)
endif()


## Optional ones
if (SOFAGUI_ENABLE_QWT)
    message("Qwt activated")
    add_subdirectory(qwt-6.1.2/src qwt)
endif()

option(SOFA_BUILD_MINIFLOWVR "Build the miniFlowVR library distributed in the extlibs/ directory." OFF)
if (SOFA_BUILD_MINIFLOWVR)
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

