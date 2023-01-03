# CMakeList.txt : CMake project for git-lfs-lib, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

project ("git-lfs-lib")


list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(conan_install)
OPTION (ENABLE_UNIT_TEST "Enable unite tests" ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS ON)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)



# Add source to this project's executable.
add_subdirectory("src")

IF (ENABLE_UNIT_TEST)
message(STATUS "Test are enabled in ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}-test.exe ") 
enable_testing()
add_subdirectory("test")
ENDIF()



#add_executable( ${PROJECT_NAME} "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}-test.exe" )

#add_test( ${PROJECT_NAME} "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}-test.exe" )
# TODO: Add tests and install targets if needed.
