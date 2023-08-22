#ifndef __VSNC_FILES_H__
#define __VSNC_FILES_H__
#include "../vsnc_utils.h"

namespace vsnc
{
	namespace utils
	{
		/**
		 * @brief 文件类
		*/
		class VFile
		{
		public:
			/**
			 * @brief         获取文件夹下所有文件
			 * @param files   返回文件路径列表
			 * @param path    文件夹路径
			 * @param subfix  过滤
			 * @return        无
			*/
			static void        GetListAllFile(std::list<std::string>& __VSNC_OUT files, const std::string& __VSNC_IN path, const std::string& __VSNC_IN subfix = "") noexcept;

			/**
			 * @brief         创建文件夹
			 * @param dirname 文件夹名称
			 * @return        成功返回ture,错误返回false
			*/
			static bool        Mkdir(const char* __VSNC_IN dirname) noexcept;

			/**
			 * @brief 删除文件/文件夹
			 * @param path 文件路径
			 * @return 成功返回ture,错误返回false
			*/
			static bool        Rm(const char* __VSNC_IN path) noexcept;

			/**
			 * @brief 复制
			 * @param from 被复制的文件路径 
			 * @param to 新复制的文件路径
			 * @param flag 是否覆盖标志
			 * @return 成功返回ture,错误返回false
			*/
			static bool        Copy(const std::string& __VSNC_IN from, const std::string& __VSNC_IN to, const bool __VSNC_IN flag = false) noexcept;

			/**
			 * @brief  获取真实的文件路径
			 * @param path 路径
			 * @param rpath 真实路径
			 * @return 成功返回ture,错误返回false
			*/
			static bool        GetRealpath(const std::string& __VSNC_IN path, std::string& __VSNC_OUT rpath) noexcept;

			/**
			 * @brief 获取文件夹名
			 * @param filename 文件路径
			 * @return 成功返回ture,错误返回false
			*/
			static std::string GetDirname(const std::string& __VSNC_IN filename) noexcept;

			/**
			 * @brief 获取文件名
			 * @param filename 文件路径
			 * @return 成功返回ture,错误返回false
			*/
			static std::string GetBasename(const std::string& __VSNC_OUT filename) noexcept;

			/**
			 * @brief 打开if
			 * @param ifs 句柄
			 * @param filename 文件路径 
			 * @param mode 输入模式
			 * @return 成功返回ture,错误返回false
			*/
			static bool        OpenForRead(std::ifstream& __VSNC_IN_OUT ifs, const std::string& __VSNC_IN filename, const std::ios_base::openmode __VSNC_IN mode) noexcept;

			/**
			 * @brief 打开of
			 * @param ofs 句柄
			 * @param filename 文件路径 
			 * @param mode 输入模式
			 * @return 成功返回ture,错误返回false
			*/
			static bool        OpenForWrite(std::ofstream& __VSNC_IN_OUT ofs, const std::string& __VSNC_IN filename, const std::ios_base::openmode __VSNC_IN mode) noexcept;
			/**
			 * @brief 写入文件
			 * @param filename 文件名 
			 * @param context  字符串内容
			 * @param mode     写入模式
			 * @return 成功返回ture,错误返回false
			*/
			static bool        WriteString(const std::string& __VSNC_IN filename, const std::string& __VSNC_IN context, const std::ios_base::openmode __VSNC_IN mode = std::ios_base::app) noexcept;

			/**
			 * @brief 写入文件
			 * @param filename 文件名 
			 * @param context  字符串内容
			 * @param mode     写入模式
			 * @return 成功返回ture,错误返回false
			*/
			static bool        WriteString(const char* __VSNC_IN filename, const std::string& __VSNC_IN context, const std::ios_base::openmode __VSNC_IN mode = std::ios_base::app) noexcept;

			/**
			 * @brief 写入流
			 * @param filename 文件名 
			 * @param data     指针头
			 * @param length   长度
			 * @param mode     写入模式
			 * @return 成功返回ture,错误返回false
			*/

			static bool        WriteStream(const  std::string& __VSNC_IN filename, uint8_t* __VSNC_IN data, const size_t __VSNC_IN length, const std::ios_base::openmode __VSNC_IN mode = std::ios_base::app) noexcept;
			
			/**
			 * @brief 写入流
			 * @param filename 文件名
			 * @param data     指针头
			 * @param length   长度
			 * @param mode     写入模式
			 * @return 成功返回ture,错误返回false
			*/
			static bool        WriteStream(const char* __VSNC_IN filename, uint8_t* __VSNC_IN data, const size_t __VSNC_IN length, const std::ios_base::openmode __VSNC_IN mode = std::ios_base::app) noexcept;
		};
	}
}

#endif // !__VSNC_FILES_H__
