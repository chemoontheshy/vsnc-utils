# 要求最低Cmake版本
cmake_minimum_required(VERSION 3.15)
# 项目名称
project(vsnc-utils)
# C++标准
set(CMAKE_CXX_STANDARD 11)


# 输出目录，${PROJECT_BINARY_DIR}为Cmake命令执行的位置
##Output path
IF (WIN32)
	MESSAGE(STATUS "Now is windows")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/x86)
    SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/x86)
    SET(CMAKE_INSTALL_PREFIX  ${PROJECT_SOURCE_DIR}/install/x86)
ELSEIF (APPLE)
	MESSAGE(STATUS "Now is Apple systens.")
    SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/ios)
    SET(CMAKE_INSTALL_PREFIX  ${PROJECT_SOURCE_DIR}/install/ios)
ELSEIF (UNIX)
    MESSAGE(STATUS "Now is UNIX systens.")
	SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/unix)
    SET(CMAKE_INSTALL_PREFIX  ${PROJECT_SOURCE_DIR}/install/unix)
ENDIF ()
# 添加子目录，子目录下必须有CMakeLists.txt
add_subdirectory(src)
add_subdirectory(example)