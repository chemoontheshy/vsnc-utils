#Set the munimum version of CMake that can be used
cmake_minimum_required(VERSION 3.5)

#set the project name
project (logTest)

# 将当前目录下所有源码文件添加到变量math_src
aux_source_directory(. logTest_src)

SET(3RD ${CMAKE_SOURCE_DIR}/3rdparty)

# link include
INCLUDE_DIRECTORIES(${3RD}/include)

# link lib
LINK_DIRECTORIES(${3RD}/lib)

#Output path
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME})

# 头文件搜索的路径
include_directories(${CMAKE_SOURCE_DIR}/src)

#Add an executalbe
add_executable(${PROJECT_NAME} ${logTest_src})


#link the shared
target_link_libraries(${PROJECT_NAME} utils)