project(logger)
# 将当前目录下所有源码文件添加到变量math_src
aux_source_directory(. logger_src)
# 生成动态链接库
add_library(${PROJECT_NAME} OBJECT ${logger_src})
# 头文件搜索的路径
include_directories(${CMAKE_SOURCE_DIR}/src)