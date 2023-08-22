project(token)
# 将当前目录下所有源码文件添加到变量math_src
aux_source_directory(. token_src)
# 生成动态链接库
add_library(${PROJECT_NAME} OBJECT ${token_src})

target_compile_definitions(${PROJECT_NAME} PRIVATE NOMINMAX)
# link include lib
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/3rdparty/include)

# 头文件搜索的路径
include_directories(${CMAKE_SOURCE_DIR}/src)
