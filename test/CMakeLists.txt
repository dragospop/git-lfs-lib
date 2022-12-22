﻿# CMakeList.txt : CMake project for git-lfs-lib, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)


message(STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY_1 = ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")


# include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
# conan_basic_setup()

# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_autodetect(settings)

conan_cmake_install(PATH_OR_REFERENCE .
                    BUILD missing
                    REMOTE conancenter
                    SETTINGS ${settings})

# message(STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY_3 = ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
# conan_cmake_run(CONANFILE conanfile.txt  # or relative build/conanfile.txt
#                 BASIC_SETUP CMAKE_TARGETS
#                 INSTALL_FOLDER "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
#                 BUILD missing)
# 
# message(STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY_4 = ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
include(${CMAKE_BINARY_DIR}/test/conanbuildinfo_multi.cmake)
# 
conan_basic_setup()
# 
message(STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY_5 = ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
project ("git-lfs-lib-test")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest)

list(APPEND GIT_LFS_LIB_TEST_SRCS src/main.cpp src/lfs_pointer_test.cpp)



add_executable (${PROJECT_NAME} ${GIT_LFS_LIB_TEST_SRCS})

message(STATUS "git-lfs-lib_BINARY_DIR=${git-lfs-lib_BINARY_DIR}")


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

foreach(_LIB ${CONAN_LIBS_RELEASE})
    target_link_libraries(${PROJECT_NAME} optimized ${_LIB})
endforeach()
foreach(_LIB ${CONAN_LIBS_DEBUG})
    target_link_libraries(${PROJECT_NAME} debug ${_LIB})
endforeach()

message(STATUS "ProjectName = ${PROJECT_NAME}")
message(STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY = ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")
message(STATUS "TARGET_FILE_DIR = $<TARGET_FILE_DIR:exe>")