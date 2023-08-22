#ifndef __VSNC_COMMON_UTILS_H_
#define __VSNC_COMMON_UTILS_H_
#include "vsnc_utils.h"


// �ṩһ��C�ӿ�
#ifdef __cplusplus
extern "C" {
#endif
    namespace vsnc
    {
        namespace utils
        {
            /**
             * @brief         �����ļ���
             * @param dirname �ļ�������
             * @return        �ɹ�����ture,���󷵻�false
            */
            __VSNC_PORT bool mkdir(const char* __VSNC_IN filename);

            /**
             * @brief ɾ���ļ�/�ļ���
             * @param path �ļ�·��
             * @return �ɹ�����ture,���󷵻�false
            */
            __VSNC_PORT bool rm(const char* __VSNC_IN path);

            /**
             * @brief ����
             * @param from �����Ƶ��ļ�·��
             * @param to �¸��Ƶ��ļ�·��
             * @param flag �Ƿ񸲸Ǳ�־
             * @return �ɹ�����ture,���󷵻�false
            */
            __VSNC_PORT bool copy(const char* __VSNC_IN from, const char* __VSNC_IN to, const bool __VSNC_IN flag = false);

            /**
             * @brief  ��ȡ��ʵ���ļ�·��
             * @param path ·��
             * @param rpath ��ʵ·��
             * @return �ɹ�����ture,���󷵻�false
            */
            __VSNC_PORT bool get_real_path(const char* __VSNC_IN path, char* __VSNC_OUT rpath);

            /**
             * @brief ��ȡ�ļ�����
             * @param inFileName �ļ�·��
             * @param outFile �ļ�����
             * @return �ɹ�����ture,���󷵻�false
            */
            __VSNC_PORT bool get_dir_name(const char* __VSNC_IN inFileName, char* __VSNC_OUT outFile);


            /**
             * @brief ��ȡ�ļ���
             * @param inFileName �ļ�·��
             * @param outFile �ļ���
              * @return �ɹ�����ture,���󷵻�false
            */
            __VSNC_PORT bool get_base_name(const char* __VSNC_IN inFileName, char* __VSNC_OUT outFile);

            /**
             * @brief д�����ݣ�Ĭ��׷��ģʽ
             * @param filename �ļ��� 
             * @param context ����
             * @return �ɹ�����ture,���󷵻�false
            */
            __VSNC_PORT bool write_string(const char* __VSNC_IN filename, const char* __VSNC_IN content);


            /**
             * @brief д�������
             * @param filename �ļ���
             * @param data ����ָ��ͷ
             * @param length ����ָ�볤��
             * @return �ɹ�����ture,���󷵻�false
            */
            __VSNC_PORT bool write_stream(const char* __VSNC_IN filename, char* __VSNC_IN data, const int __VSNC_IN length);


            /**
             * @brief ������־��
             * @param name ��־������
             * @param printFlag ��ӡ��־
             * @param writeFlag д���־
             * @param filePath  д���ļ�
             * @param level     ����ȼ� Ĭ����3INFO
             * @return �ɹ�����true,���󷵻�false
            */
            __VSNC_PORT bool create_logger(const char* __VSNC_IN name, const bool __VSNC_IN printFlag = true, const bool __VSNC_IN writeFlag = false,const char* __VSNC_IN filePath = "", const int level = 3);

            /**
             * @brief ɾ����־��
             * @param name ��־������
             * @return �ɹ�����true,���󷵻�false
            */
            __VSNC_PORT bool delete_logger(const char* __VSNC_IN name);

            /**
             * @brief ��������ȼ�
             * @param name ��־������
             * @param level �ȼ�
            */
            __VSNC_PORT void set_output_level(const char* __VSNC_IN name, const int level);

            /**
             * @brief ����־����ӡ
             * @param name file �ļ���
             * @param level line ����
             * @param file elapse �����¼�
             * @param line ����
             * @param elapse �����¼�
             * @param timestamp ʱ���
             * @param pid ����ID
             * @param tid �߳�ID
             * @param content ����
            */
            __VSNC_PORT void vsnc_log(const char* __VSNC_IN name, const int __VSNC_IN level, const char* __VSNC_IN file, const int64_t __VSNC_IN line, int64_t __VSNC_IN elapse, int64_t __VSNC_IN timestamp, size_t __VSNC_IN pid, size_t __VSNC_IN tid, const char* __VSNC_IN content);

            /**
             * @brief ����־����ӡ
             * @param name file �ļ���
             * @param level line ����
             * @param file elapse �����¼�
             * @param line ����
             * @param elapse �����¼�
             * @param timestamp ʱ���
             * @param pid ����ID
             * @param tid �߳�ID
             * @param content ����
            */
            __VSNC_PORT void vsnc_root_log(const char* __VSNC_IN name, const int __VSNC_IN level, const char* __VSNC_IN file, const int64_t __VSNC_IN line, int64_t __VSNC_IN elapse, int64_t __VSNC_IN timestamp, size_t __VSNC_IN pid, size_t __VSNC_IN tid, const char* __VSNC_IN content);

        }
    }

#ifdef __cplusplus
}
#endif

//������ӡ����־��
#define VSNC_GET_LOG_CREATE(name,print,write,filePath,level) vsnc::utils::create_logger(name,print,write,filePath,level)
// ������ӡ��־��
#define VSNC_GET_PRINT_CREATE(name)                          vsnc::utils::create_logger(name)
// ����д����־��
#define VSNC_GET_WRTIE_CREATE(name,filePath)                 vsnc::utils::create_logger(name,false,true,filePath)
// ������ӡ/д����־��
#define VSNC_GET_ALL_CREATE(name,filePath)                   vsnc::utils::create_logger(name,true,true,filePath)
// ��������ȼ�
#define VSNC_SET_OUTPUT_LEVLE(name,level)                    vsnc::utils::set_output_level(name,level)         
//����־��
#define VSNC_LOG_LOG(name,level,content)                     vsnc::utils::vsnc_log(name,level,__FILE__, __LINE__,0, vsnc::utils::__utc(), vsnc::utils::__get_pid(), vsnc::utils::__get_thread_id(),content)
#define VSNC_LOG_TRACE(name,content)                         VSNC_LOG_LOG(name,1,content)
#define VSNC_LOG_DEBUG(name,content)                         VSNC_LOG_LOG(name,2,content)
#define VSNC_LOG_INFO(name,content)                          VSNC_LOG_LOG(name,3,content)
#define VSNC_LOG_WARN(name,content)                          VSNC_LOG_LOG(name,4,content)
#define VSNC_LOG_ERROR(name,content)                         VSNC_LOG_LOG(name,5,content)
#define VSNC_LOG_FATAL(name,content)                         VSNC_LOG_LOG(name,6,content)
//����־��
#define VSNC_ROOT_LOG(level,content)                         vsnc::utils::vsnc_root_log(name,level,__FILE__, __LINE__,0, vsnc::utils::__utc(), vsnc::utils::__get_pid(), vsnc::utils::__get_thread_id(),content)
#define VSNC_ROOT_TRACE(content)                             VSNC_ROOT_LOG(1,content)
#define VSNC_ROOT_DEBUG(content)                             VSNC_ROOT_LOG(2,content)
#define VSNC_ROOT_INFO(content)                              VSNC_ROOT_LOG(3,content)
#define VSNC_ROOT_WARN(content)                              VSNC_ROOT_LOG(4,content)
#define VSNC_ROOT_ERROR(content)                             VSNC_ROOT_LOG(5,content)
#define VSNC_ROOT_FATAL(content)                             VSNC_ROOT_LOG(6,content)


#endif // !__VSNC_COMMON_UTILS_H_
