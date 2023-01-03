# CMakeList.txt : CMake project for git-lfs-lib, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)
project ("git-lfs-lib-test")
INSTALL_CONAN_DEPS()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest)

list(APPEND GIT_LFS_LIB_TEST_SRCS src/main.cpp src/lfs_pointer_test.cpp)



add_executable (${PROJECT_NAME} ${GIT_LFS_LIB_TEST_SRCS})


set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${PROJECT_NAME} PUBLIC
  $GTest_INCLUDE_DIR
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
  $<INSTALL_INTERFACE:include/git-lfs-lib>  # <prefix>/include/mylib
)

target_link_directories(${PROJECT_NAME} PUBLIC ${git-lfs-lib_BINARY_DIR})
target_link_libraries(${PROJECT_NAME} git-lfs-lib)


#gtest_discover_tests(${PROJECT_NAME} TEST_PREFIX gtest)
#add_test(NAME unit_tst COMMAND ${PROJECT_NAME})

message(STATUS "CONAN_LIBS = ${CONAN_LIBS}")
message(STATUS "CONAN_LIBS_RELEASE = ${CONAN_LIBS_RELEASE}")
message(STATUS "CONAN_LIBS_DEBUG = ${CONAN_LIBS_DEBUG}")

CONAN_MULTI_LINK(${PROJECT_NAME})

message(STATUS "ProjectName = ${PROJECT_NAME}")
message(STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY = ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")
message(STATUS "TARGET_FILE_DIR = $<TARGET_FILE_DIR:exe>")