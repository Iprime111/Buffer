cmake_minimum_required (VERSION 3.8 FATAL_ERROR)

project (Buffer)

add_library (${PROJECT_NAME} INTERFACE)

target_include_directories (${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/libs/CustomAssert)
