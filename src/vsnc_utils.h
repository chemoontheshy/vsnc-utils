#ifndef __VSNC_UTILS_H__
#define __VSNC_UTILS_H__


/**
* @file       vsnc_utils.h
* @brief	  常用工具类
* @author     chemoontheshy
* @email      570635410@qq.com
* @date		  2023-07-04 09:42:29
* @copyright  Copyright (c) 2023年 chemoontheshy all rights reserved
*/



#include <chrono>
#include <thread> // std::this_thread
#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#ifdef _WIN32
#include <Windows.h>
#else
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#endif // WIN



#ifdef _WIN32
//#ifdef _WINDLL
#ifdef _WIN32
#define __VSNC_PORT __declspec(dllexport)
#else
#define __VSNC_PORT __declspec(dllimport)
#endif // WIN32_DLL

#define __VSNC_IN     // 输入参数
#define __VSNC_OUT    // 输出参数
#define __VSNC_IN_OUT // 输入输出参数
#endif // !

#define VSNC_MAX(a,b)          ((a)>(b)?(a):(b))
#define VSNC_MIN(a,b)          ((a)<(b)?(a):(b))

/**
 * @brief 接口通用回复
*/
enum class Result : int8_t
{
	/**
	 * @brief 方法未实现
	*/
	UNIMPLEMENTED = -1,
	/**
	 * @brief 方法执行失败
	*/
	FAILURE = 0,
	/**
	 * @brief 方法执行成功获取以毫秒为单位的UTC时间当前线程以秒为单位延时延迟的秒数<
	*/
	SUCCESS = 1
};

namespace vsnc
{
	namespace utils
	{
		/**
		 * @brief 获取以毫秒为单位的UTC时间
		 * @return 以毫秒为单位的UTC时间
		*/
		inline static int64_t     __utc() noexcept { return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(); }

		/**
		 * @brief 以秒为单位延时
		 * @param val 延迟的秒数
		 * @return 无
		*/
		inline static void        __sleep_seconds(const int val) noexcept { std::this_thread::sleep_for(std::chrono::seconds(val)); }

		/**
		 * @brief 以毫秒为单位延时
		 * @param val 延迟的毫秒数
		 * @return 无
		*/
		inline static void        __sleep_milliseconds(const int val) noexcept { std::this_thread::sleep_for(std::chrono::milliseconds(val)); }

		/**
		 * @brief 获取当前线程的ID
		 * @return 当前线程的ID
		*/
		inline static size_t      __get_thread_id() noexcept {
			auto id = std::this_thread::get_id();
			std::stringstream ss;
			ss << id;
			return static_cast<size_t>(std::stoi(ss.str()));
		}

		/**
		 * @brief 获取当前进程的ID
		 * @return 当前进程的ID
		*/
		inline static size_t     __get_pid() noexcept {
#ifdef _WIN32
			return static_cast<size_t>(GetCurrentProcessId());
#else
			return static_cast<size_t>(getpid());
#endif // _WIN32

			
		}
	}
}

namespace vsnc
{
	namespace utils
	{
		/// <summary>
		/// 单例模式封装类
		/// </summary>
		/// <typeparam name="T">类型</typeparam>
		/// <typeparam name="X">为创造多个实例对应的Tag</typeparam>
		/// <typeparam name="N">同一Tag创造多个实例索引</typeparam>
		template<class T, class X, size_t N>
		T& GetInstanceX()
		{
			static T v;
			return v;
		}

		/**
		 * @brief 单例模式封装类
		 * @tparam T 类型
		 * @tparam X 为创造多个实例对应的Tag
		 * @tparam N 同一Tag创造多个实例索引
		 * @return 智能指针
		*/
		template<class T, class X = void, size_t N>
		std::shared_ptr<T> GetInstancePtr()
		{
			static std::shared_ptr<T> v(new T);
			return v;
		}
		/**
		 * @brief 单例模式封装类
		 * @tparam T 类型
		 * @tparam X 为创造多个实例对应的Tag
		 * @tparam N 同一Tag创造多个实例索引
		*/
		template<class T, class X = void, size_t N = 0 >
		class Singleton
		{
		public:
			/**
			 * @brief 获取单例的裸指针
			 * @return 裸指针
			*/
			static T* GetInstance()
			{
				static T v;
				return &v;
			}
		};

		/**
		 * @brief 单例模式封装类
		 * @tparam T 类型
		*/
		template<class T>
		class SingletonPtr
		{
		public:
			/**
			 * @brief 获取单例智能指针
			 * @return 单例智能指针
			*/
			static std::shared_ptr<T> GetInstance()
			{
				static std::shared_ptr<T> v(new T());
				return v;
			}
			~SingletonPtr()
			{
				std::cout << "Destruction" << std::endl;
			}
		};
	}
}



#endif // !__VSNC_UTILS_H__
