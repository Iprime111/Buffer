cmake_minimum_required (VERSION 3.8 FATAL_ERROR)

project (Buffer)

if (NOT TARGET Buffer)

include_directories (Buffer ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/libs/CustomAssert)

endif ()
