# CMakeList.txt : CMake project for git-lfs-lib, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)


project ("git-lfs-lib")


OPTION (BUILD_SHARED_LIBS "Build Shared Libraries" ON)
# Set the LIB_TYPE variable to STATIC

IF (BUILD_SHARED_LIBS)
  # User wants to build Dynamic Libraries,
  # so change the LIB_TYPE variable to CMake keyword 'SHARED'
  SET (LIB_TYPE SHARED)
ELSE()
  SET (LIB_TYPE STATIC)
ENDIF (BUILD_SHARED_LIBS)

message(STATUS "Buildin library as ${LIB_TYPE} ") 




set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(INCLUDE_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../include/git-lfs-lib )
set(LIB_INSTALL_DIR "lib" )



list(APPEND GIT_LFS_LIB_SRCS "lfs/lfs_pointer.cpp" "lfs/lfs_pointer.cpp")

list(APPEND GIT_LFS_LIB_ALL_HEADERS "lfs/lfs_pointer.h" "lfs/lfs_comm.h" "dll_export.h" "string_utils.h")

file(COPY ${GIT_LFS_LIB_ALL_HEADERS}
    DESTINATION ${INCLUDE_INSTALL_DIR}
    FILES_MATCHING
        PATTERN *.h
)


message(STATUS "CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR} ") 



# Add source to this project's executable.
#add_library (git-lfs-lib SHARED "git-lfs-lib.cpp" "git-lfs-lib.h")
add_library (git-lfs-lib ${LIB_TYPE} ${GIT_LFS_LIB_SRCS} ${GIT_LFS_LIB_ALL_HEADERS} "lfs/lfs_comm.cpp" "lfs/lfs_comm.h")
set_target_properties(git-lfs-lib PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(git-lfs-lib PUBLIC
  $<INSTALL_INTERFACE:include/git-lfs-lib>  # <prefix>/include/mylib
  ${CMAKE_CURRENT_SOURCE_DIR}
)


IF (BUILD_SHARED_LIBS)
  SET_TARGET_PROPERTIES (${PROJECT_NAME} PROPERTIES DEFINE_SYMBOL  "GIT_LFS_LIB_EXTPORTS" )
ELSE()
  SET_TARGET_PROPERTIES (${PROJECT_NAME} PROPERTIES DEFINE_SYMBOL  "GIT_LFS_LIB_EXTPORTS_STATIC" )
ENDIF (BUILD_SHARED_LIBS)
# include (GenerateExportHeader)
# 
# GENERATE_EXPORT_HEADER( ${PROJECT_NAME}
#              BASE_NAME GIT_LFS_LIB
#              EXPORT_MACRO_NAME GIT_LFS_LIB_DLL_EXPORT
#              EXPORT_FILE_NAME GIT_LFS_LIB_Export.h
#              STATIC_DEFINE GIT_LFS_LIB_BUILT_AS_STATIC
# )

message(STATUS "LIBRARY_INSTALL_DIR=${LIBRARY_INSTALL_DIR} ") 
#install(TARGETS ${PROJECT_NAME} DESTINATION ${LIBRARY_INSTALL_DIR})
install(
    TARGETS ${PROJECT_NAME}
    EXPORT "${PROJECT_NAME}"
    LIBRARY DESTINATION "lib"
    ARCHIVE DESTINATION "lib"
    RUNTIME DESTINATION "bin"
    INCLUDES DESTINATION "${include_install_dir}"
)

message(STATUS "INCLUDE_INSTALL_DIR=${INCLUDE_INSTALL_DIR} ") 

install(FILES
 ${GIT_LFS_LIB_ALL_HEADERS}
 DESTINATION 
 ${INCLUDE_INSTALL_DIR}
)


#install(FILES
# GIT_LFS_LIB_ALL_HEADERS
# ${PROJECT_BINARY_DIR}/somelib_export.h DESTINATION ${INCLUDE_INSTALL_DIR}
#)


# TODO: Add tests and install targets if needed.
