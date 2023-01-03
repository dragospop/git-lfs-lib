
macro(INSTALL_CONAN_DEPS)
    set(BK_CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    set(BK_CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
    
    # Download automatically, you can also just copy the conan.cmake file
    if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
        message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
        file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake")
    endif()

    include(${CMAKE_BINARY_DIR}/conan.cmake)

    set(CMAKE_CURRENT_BINARY_DIR ${CMAKE_BINARY_DIR})
    set(CONAN_OUT_FOLDER ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
    message(STATUS "CONAN_OUT_FOLDER = " ${CONAN_OUT_FOLDER})

    conan_cmake_run(CONANFILE conanfile.txt
                    INSTALL_FOLDER ${CONAN_OUT_FOLDER}
                    BUILD "missing"
                    BASIC_SETUP)

    include(${CONAN_OUT_FOLDER}/conanbuildinfo_multi.cmake)
    conan_basic_setup(TARGETS)

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BK_CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    set(CMAKE_CURRENT_BINARY_DIR ${BK_CMAKE_CURRENT_BINARY_DIR})
endmacro()

macro(CONAN_MULTI_LINK TARGET_NAME)
#foreach(_LIB ${CONAN_LIBS})
#    target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
#endforeach()

#foreach(_LIB ${CONAN_LIBS_RELEASE})
#    target_link_libraries(${PROJECT_NAME} optimized ${_LIB})
#    message(STATUS "Lib = ${_LIB}")
#endforeach()
#foreach(_LIB ${CONAN_LIBS_DEBUG})
#    target_link_libraries(${PROJECT_NAME} debug ${_LIB})
#    message(STATUS "Lib = ${_LIB}")
#endforeach()
conan_target_link_libraries(${TARGET_NAME})
endmacro()