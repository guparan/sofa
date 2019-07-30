cmake_minimum_required(VERSION 3.1)
project(SofaTest_test)

find_package(SofaPython QUIET)

set(HEADER_FILES
)

set(SOURCE_FILES
)

set(TEST_FILES
    scenes/damping.py
    python_tests/python_test_test.py
    )

if(SofaPython_FOUND)
    target_compile_definitions(${PROJECT_NAME} PUBLIC "-DSOFATEST_PYTHONTESTS_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/python_tests\"")
    target_compile_definitions(${PROJECT_NAME} PUBLIC "-DSOFATEST_SCENES_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/scenes\"")
    list(APPEND SOURCE_FILES "python_test_list.cpp")
endif()

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} ${TEST_FILES})
#target_compile_definitions(${PROJECT_NAME} "-DSOFA_SRC_DIR=\"${CMAKE_SOURCE_DIR}\"")
target_link_libraries(${PROJECT_NAME} PUBLIC SofaTest SofaGTestMain)

if(SofaPython_FOUND)
    target_link_libraries(${PROJECT_NAME} PUBLIC SofaPython)
endif()
