# 包含子目录

project(utils)

add_subdirectory(files)
add_subdirectory(logger)
add_subdirectory(token)

IF (WIN32)
    MESSAGE(STATUS "link include lib is Win.")    
	LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/3rdparty/lib)
ELSEIF (APPLE)
	MESSAGE(STATUS "Now is Apple systens.")
ELSEIF (UNIX)
	MESSAGE(STATUS "link include lib i is UNIX")
ENDIF ()
# 链接子目录生成的OBJECT生成库

# 将当前目录下所有源码文件添加到变量math_src
aux_source_directory(. src_src)

add_library(${PROJECT_NAME} SHARED ${src_src} 
						 $<TARGET_OBJECTS:files> 
						 $<TARGET_OBJECTS:logger>
						 $<TARGET_OBJECTS:token>)


						 # 头文件搜索的路径
include_directories(${CMAKE_SOURCE_DIR}/src)
# 依赖math动态链接库

# link lib
target_link_libraries(${PROJECT_NAME} libcrypto libssl)



#include 
SET(HeaderFile ${CMAKE_SOURCE_DIR}/src/vsnc_utils.h
               ${CMAKE_SOURCE_DIR}/src/common_utils.h)

INSTALL(FILES ${HeaderFile} DESTINATION include)
install(TARGETS ${PROJECT_NAME}
        EXPORT utilsTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION lib
        PUBLIC_HEADER DESTINATION include
        )

