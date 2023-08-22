#ifndef __VSNC_LOGGER_H__
#define __VSNC_LOGGER_H__
#include "../vsnc_utils.h"
#include <map>

namespace vsnc
{
	namespace log
	{
		/**
		 * @brief 日志等级
		*/
		enum class LOGLevel : size_t
		{
			/**
			 * @brief 未知等级
			*/
			LOG_UNKNOW,
			/**
			 * @brief 追踪等级
			*/
			LOG_TRACE,
			/**
			 * @brief 指出细粒度信息事件对调试应用程序是非常有帮助的，主要用于开发过程中打印一些运行信息。
			*/
			LOG_DEBUG,
			/**
			 * @brief 消息在粗粒度级别上突出强调应用程序的运行过程。打印一些你感兴趣的或者重要的信息，这个可以用于生产环境中输出程序运行的一些重要信息，但是不能滥用，避免打印过多的日志。
			*/
			LOG_INFO,
			/**
			 * @brief 表明会出现潜在错误的情形，有些信息不是错误信息，但是也要给程序员的一些提示。
			*/
			LOG_WARN,
			/**
			 * @brief 指出虽然发生错误事件，但仍然不影响系统的继续运行。打印错误和异常信息，如果不想输出太多的日志，可以使用这个级别。
			*/
			LOG_ERROR,
			/**
			 * @brief 指出每个严重的错误事件将会导致应用程序的退出。这个级别比较高了。重大错误，这种级别你可以直接停止程序了
			*/
			LOG_FATAL,
		};


		/**
		 * @brief LOG日志格式
		*/
		struct LOGTime
		{
			/**
			 * @brief  years since 1900
			*/
			size_t Year;
			/**
			 * @brief  months since January - [1, 12]
			*/
			size_t Mon;
			/**
			 * @brief day of the month - [1, 31]
			*/
			size_t Day;
			/**
			 * @brief hours since midnight - [0, 23]
			*/
			size_t Hour;
			/**
			 * @brief  minutes after the hour - [0, 59]
			*/
			size_t Min;
			/**
			 * @brief seconds after the minute - [0, 59] including leap second
			*/
			size_t Sec;
			/**
			 * @brief seconds after the seconds - [0, 999] including leap second
			*/
			size_t Mil;
		};

		/**
		 * @brief 日志事件参数
		*/
		struct LOGEventParam
		{
			/**
			 * @brief 文件名
			*/
			std::string FileName;
			/**
			 * @brief 行数
			*/
			int64_t     Line;
			/**
			 * @brief  启动时间经过时间（毫秒）
			*/
			int64_t     Elapse;
			/**
			 * @brief  当前时间时间戳
			*/
			int64_t     Timestamp;
			/**
			 * @brief 进程ID
			*/
			size_t      ProccessID;
			/**
			 * @brief 线程ID
			*/
			size_t      ThreadID;
			/**
			 * @brief 内容
			*/
			std::string Content;
		};

		/**
		 * @brief 日志器参数
		*/
		struct LoggerParam
		{
			/**
			 * @brief 日志名称
			*/
			std::string Name;
			/**
			 * @brief 打印标志
			*/
			bool        PrintFlag;
			/**
			 * @brief 写入文件标志
			*/
			bool        WriteFlag;
			/**
			 * @brief 写入文件路径
			*/
			std::string FilePath;
		};

		/**
		 * @brief 日志事件
		*/
		class LogEvent
		{
		public:
			~LogEvent() = default;

			/**
			 * @brief 组文件格式 
			 * @param loggerName 文件名 
			 * @param level 日志等级
			 * @return 组好文件格式后的字符串
			*/
			virtual std::string GetFormat(const std::string& __VSNC_IN loggerName, const LOGLevel __VSNC_IN level) noexcept = 0;
		};

		using LogEventPtr = std::shared_ptr<LogEvent>;
		
		/**
		 * @brief 创建日志事件
		 * @param logEventParam 日志参数
		 * @return 日志事件指针
		*/
		LogEventPtr CreateLogEventPtr(const LOGEventParam& __VSNC_IN logEventParam);

		/**
		 * @brief 日志管理器
		*/
		class Logger
		{
		public:
			/*
			* 析构函数
			*/
			~Logger() = default;


			/**
			 * @brief 设置输出等级（输出等级应该可以由外部决定
			 * @param  输出等级
			*/
			virtual void SetOutputLevel(const LOGLevel __VSNC_IN level) noexcept = 0;

			/**
			 * @brief 日志输出
			 * @param level 日志等级
			 * @param ptrLogEvent 日志事件指针
			*/
			virtual void Log(const LOGLevel __VSNC_IN level, LogEventPtr __VSNC_IN ptrLogEvent) noexcept = 0;

			/**
			 * @brief Trace日志输出
			 * @param ptrLogEvent 日志事件指针
			*/
			virtual void Trace(LogEventPtr  __VSNC_IN ptrLogEvent) noexcept = 0;

			/**
			 * @brief Debug日志输出
			 * @param ptrLogEvent 日志事件指针
			*/
			virtual void Debug(LogEventPtr  __VSNC_IN ptrLogEvent) noexcept = 0;

			/**
			 * @brief Info日志输出
			 * @param ptrLogEvent 日志事件指针
			*/
			virtual void Info(LogEventPtr   __VSNC_IN ptrLogEvent) noexcept = 0;

			/**
			 * @brief Warn日志输出
			 * @param ptrLogEvent 日志事件指针
			*/
			virtual void Warn(LogEventPtr   __VSNC_IN ptrLogEvent) noexcept = 0;

			/**
			 * @brief Error日志输出
			 * @param ptrLogEvent 日志事件指针
			*/
			virtual void Error(LogEventPtr  __VSNC_IN ptrLogEvent) noexcept = 0;

			/**
			 * @brief Fatal日志输出
			 * @param ptrLogEvent 日志事件指针
			*/
			virtual void Fatal(LogEventPtr  __VSNC_IN ptrLogEvent) noexcept = 0;
		};
		/**
		 * @brief 指定别名
		*/
		using LoggerPtr = std::shared_ptr<Logger>;


		/**
		 * @brief 日志管理器
		*/
		class LoggerManager
		{
		public:
			/**
			 * @brief 析构函数
			*/
			~LoggerManager() = default;

			/**
			 * @brief 创建日志器
			 * @param name 日志器名称
			 * @param printFlag 是否打印标志
			 * @param writeFlag 是否写入文件标志
			 * @param filePath 文件路径，只有writeFlag为true才会写入
			 * @return 成功返回日志器指针,错误返回空指针（所以必须返回时必须先判断是否为空指针）
			*/
			virtual LoggerPtr              CreateLoggerPtr(const std::string& __VSNC_IN name, const bool __VSNC_IN printFlag = true, const bool __VSNC_IN writeFlag = false, const std::string& __VSNC_IN filePath = "") noexcept = 0;

			/**
			 * @brief 删除日志器
			 * @param loggerName 日志器名称
			 * @return 成功返回true,错误返回false,如果日志器列表里没有就返回false
			*/
			virtual bool                   Delete(const std::string& __VSNC_IN loggerName)       noexcept = 0;


			/**
			 * @brief 获取日志器名称列表
			 * @return 日志器名称列表
			*/
			virtual std::list<std::string> GetListLoggerName()                                   noexcept = 0;

			/**
			 * @brief 获取子日志器指针
			 * @param loggerName 子日志器名称
			 * @return 子日志器指针
			*/
			virtual LoggerPtr              GetLoggerPtr(const std::string& __VSNC_IN loggerName) noexcept = 0;

			/**
			 * @brief 获取主日志器指针
			 * @return 主日志器指针
			*/
			virtual LoggerPtr              GetLoggerRootPtr()                                    noexcept = 0;

		};

		/**
		 * @brief 指定别名
		*/
		using   LoggerMgr = std::shared_ptr<LoggerManager>;

		/**
		 * @brief 实例化日志管理器，方便实现单例模式
		*/
		class InstanceMgr
		{
		public:
			/**
			 * @brief 构造
			*/
			InstanceMgr();

			/**
			 * @brief 获取日志管理器指针
			 * @return 日志管理器指针
			*/
			LoggerMgr GetLoggerMgr() { return m_pLoggerMgr; }
		private:
			/**
			 * @brief 日志管理器指针
			*/
			LoggerMgr m_pLoggerMgr;
		};

		/**
		 * @brief 实例化单例
		*/
		typedef __VSNC_PORT vsnc::utils::SingletonPtr<InstanceMgr> SingleLogMgr;
	}
}
#endif // !__VSNC_LOGGER_H__