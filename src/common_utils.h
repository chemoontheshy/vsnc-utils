#ifndef __VSNC_COMMON_UTILS_H_
#define __VSNC_COMMON_UTILS_H_
#include "vsnc_utils.h"


// 提供一个C接口
#ifdef __cplusplus
extern "C" {
#endif
    namespace vsnc
    {
        namespace utils
        {
            /**
             * @brief         创建文件夹
             * @param dirname 文件夹名称
             * @return        成功返回ture,错误返回false
            */
            __VSNC_PORT bool mkdir(const char* __VSNC_IN filename);

            /**
             * @brief 删除文件/文件夹
             * @param path 文件路径
             * @return 成功返回ture,错误返回false
            */
            __VSNC_PORT bool rm(const char* __VSNC_IN path);

            /**
             * @brief 复制
             * @param from 被复制的文件路径
             * @param to 新复制的文件路径
             * @param flag 是否覆盖标志
             * @return 成功返回ture,错误返回false
            */
            __VSNC_PORT bool copy(const char* __VSNC_IN from, const char* __VSNC_IN to, const bool __VSNC_IN flag = false);

            /**
             * @brief  获取真实的文件路径
             * @param path 路径
             * @param rpath 真实路径
             * @return 成功返回ture,错误返回false
            */
            __VSNC_PORT bool get_real_path(const char* __VSNC_IN path, char* __VSNC_OUT rpath);

            /**
             * @brief 获取文件夹名
             * @param inFileName 文件路径
             * @param outFile 文件夹名
             * @return 成功返回ture,错误返回false
            */
            __VSNC_PORT bool get_dir_name(const char* __VSNC_IN inFileName, char* __VSNC_OUT outFile);


            /**
             * @brief 获取文件名
             * @param inFileName 文件路径
             * @param outFile 文件名
              * @return 成功返回ture,错误返回false
            */
            __VSNC_PORT bool get_base_name(const char* __VSNC_IN inFileName, char* __VSNC_OUT outFile);

            /**
             * @brief 写入内容（默认追加模式
             * @param filename 文件名 
             * @param context 内容
             * @return 成功返回ture,错误返回false
            */
            __VSNC_PORT bool write_string(const char* __VSNC_IN filename, const char* __VSNC_IN content);


            /**
             * @brief 写入二进制
             * @param filename 文件名
             * @param data 数据指针头
             * @param length 数据指针长度
             * @return 成功返回ture,错误返回false
            */
            __VSNC_PORT bool write_stream(const char* __VSNC_IN filename, char* __VSNC_IN data, const int __VSNC_IN length);


            /**
             * @brief 创建日志器
             * @param name 日志器名称
             * @param printFlag 打印标志
             * @param writeFlag 写入标志
             * @param filePath  写入文件
             * @param level     输出等级 默认是3INFO
             * @return 成功返回true,错误返回false
            */
            __VSNC_PORT bool create_logger(const char* __VSNC_IN name, const bool __VSNC_IN printFlag = true, const bool __VSNC_IN writeFlag = false,const char* __VSNC_IN filePath = "", const int level = 3);

            /**
             * @brief 删除日志器
             * @param name 日志器名称
             * @return 成功返回true,错误返回false
            */
            __VSNC_PORT bool delete_logger(const char* __VSNC_IN name);

            /**
             * @brief 设置输出等级
             * @param name 日志器名称
             * @param level 等级
            */
            __VSNC_PORT void set_output_level(const char* __VSNC_IN name, const int level);

            /**
             * @brief 子日志器打印
             * @param name file 文件名
             * @param level line 行数
             * @param file elapse 经过事件
             * @param line 行数
             * @param elapse 经过事件
             * @param timestamp 时间戳
             * @param pid 进程ID
             * @param tid 线程ID
             * @param content 内容
            */
            __VSNC_PORT void vsnc_log(const char* __VSNC_IN name, const int __VSNC_IN level, const char* __VSNC_IN file, const int64_t __VSNC_IN line, int64_t __VSNC_IN elapse, int64_t __VSNC_IN timestamp, size_t __VSNC_IN pid, size_t __VSNC_IN tid, const char* __VSNC_IN content);

            /**
             * @brief 子日志器打印
             * @param name file 文件名
             * @param level line 行数
             * @param file elapse 经过事件
             * @param line 行数
             * @param elapse 经过事件
             * @param timestamp 时间戳
             * @param pid 进程ID
             * @param tid 线程ID
             * @param content 内容
            */
            __VSNC_PORT void vsnc_root_log(const char* __VSNC_IN name, const int __VSNC_IN level, const char* __VSNC_IN file, const int64_t __VSNC_IN line, int64_t __VSNC_IN elapse, int64_t __VSNC_IN timestamp, size_t __VSNC_IN pid, size_t __VSNC_IN tid, const char* __VSNC_IN content);

        }
    }

#ifdef __cplusplus
}
#endif

//创建打印日日志器
#define VSNC_GET_LOG_CREATE(name,print,write,filePath,level) vsnc::utils::create_logger(name,print,write,filePath,level)
// 创建打印日志器
#define VSNC_GET_PRINT_CREATE(name)                          vsnc::utils::create_logger(name)
// 创建写入日志器
#define VSNC_GET_WRTIE_CREATE(name,filePath)                 vsnc::utils::create_logger(name,false,true,filePath)
// 创建打印/写入日志器
#define VSNC_GET_ALL_CREATE(name,filePath)                   vsnc::utils::create_logger(name,true,true,filePath)
// 设置输出等级
#define VSNC_SET_OUTPUT_LEVLE(name,level)                    vsnc::utils::set_output_level(name,level)         
//子日志器
#define VSNC_LOG_LOG(name,level,content)                     vsnc::utils::vsnc_log(name,level,__FILE__, __LINE__,0, vsnc::utils::__utc(), vsnc::utils::__get_pid(), vsnc::utils::__get_thread_id(),content)
#define VSNC_LOG_TRACE(name,content)                         VSNC_LOG_LOG(name,1,content)
#define VSNC_LOG_DEBUG(name,content)                         VSNC_LOG_LOG(name,2,content)
#define VSNC_LOG_INFO(name,content)                          VSNC_LOG_LOG(name,3,content)
#define VSNC_LOG_WARN(name,content)                          VSNC_LOG_LOG(name,4,content)
#define VSNC_LOG_ERROR(name,content)                         VSNC_LOG_LOG(name,5,content)
#define VSNC_LOG_FATAL(name,content)                         VSNC_LOG_LOG(name,6,content)
//主日志器
#define VSNC_ROOT_LOG(level,content)                         vsnc::utils::vsnc_root_log(name,level,__FILE__, __LINE__,0, vsnc::utils::__utc(), vsnc::utils::__get_pid(), vsnc::utils::__get_thread_id(),content)
#define VSNC_ROOT_TRACE(content)                             VSNC_ROOT_LOG(1,content)
#define VSNC_ROOT_DEBUG(content)                             VSNC_ROOT_LOG(2,content)
#define VSNC_ROOT_INFO(content)                              VSNC_ROOT_LOG(3,content)
#define VSNC_ROOT_WARN(content)                              VSNC_ROOT_LOG(4,content)
#define VSNC_ROOT_ERROR(content)                             VSNC_ROOT_LOG(5,content)
#define VSNC_ROOT_FATAL(content)                             VSNC_ROOT_LOG(6,content)


#endif // !__VSNC_COMMON_UTILS_H_
