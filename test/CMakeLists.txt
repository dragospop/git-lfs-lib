# CMakeList.txt : CMake project for git-lfs-lib, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)

set(MY_OUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
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

set(CMAKE_CURRENT_BINARY_DIR ${CMAKE_BINARY_DIR})

conan_cmake_run(CONANFILE conanfile.txt
                OUTPUT_FOLDER ${CMAKE_BINARY_DIR}
                BASIC_SETUP)

#conan_cmake_install(PATH_OR_REFERENCE .
#                    BUILD missing
#                    REMOTE conancenter
#                    SETTINGS ${settings})

message(STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY_2 = ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MY_OUT_DIR})
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

message(STATUS "CONAN_LIBS_RELEASE = ${CONAN_LIBS}")
message(STATUS "CONAN_LIBS_RELEASE = ${CONAN_LIBS_RELEASE}")
message(STATUS "CONAN_LIBS_DEBUG = ${CONAN_LIBS_DEBUG}")

foreach(_LIB ${CONAN_LIBS})
    target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
endforeach()
foreach(_LIB ${CONAN_LIBS_RELEASE})
    target_link_libraries(${PROJECT_NAME} optimized ${_LIB})
    message(STATUS "Lib = ${_LIB}")
endforeach()
foreach(_LIB ${CONAN_LIBS_DEBUG})
    target_link_libraries(${PROJECT_NAME} debug ${_LIB})
    message(STATUS "Lib = ${_LIB}")
endforeach()

message(STATUS "ProjectName = ${PROJECT_NAME}")
message(STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY = ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")
message(STATUS "TARGET_FILE_DIR = $<TARGET_FILE_DIR:exe>")