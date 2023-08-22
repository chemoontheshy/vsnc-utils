#ifndef __VSNC_LOGGER_IMPL_H__
#define __VSNC_LOGGER_IMPL_H__
#include "vsnc_logger.h"
#include <mutex>


namespace vsnc
{
	namespace log
	{
		/**
		 * @brief 日志事件实现
		*/
		class LogEventIMPL final : public LogEvent
		{
		public:
			
			/**
			 * @brief 构造函数
			 * @param param 日志参数
			*/
			LogEventIMPL(const LOGEventParam& __VSNC_IN param) :m_cParam(param) {}

			/*
			* 析构函数
			*/
			~LogEventIMPL();
			
			/**
			 * @brief 组文件格式
			 * @param loggerName 文件名
			 * @param level 日志等级
			 * @return 组好文件格式后的字符串
			*/
			std::string GetFormat(const std::string& __VSNC_IN loggerName, const LOGLevel __VSNC_IN level) noexcept;
		private:
			/**
			 * @brief 日志参数
			*/
			LOGEventParam     m_cParam;
		};

		/**
		 * @brief 日志器实现
		*/
		class LoggerIMPL final : public Logger
		{
		public:
			/**
			 * @brief 构造函数
			 * @param loggerParam 日志参数 
			*/
			LoggerIMPL(const LoggerParam& __VSNC_IN loggerParam) :m_sLoggerName(loggerParam.Name), m_bPrintFlag(loggerParam.PrintFlag),
				m_bWriteFlag(loggerParam.WriteFlag), m_sFilePath(loggerParam.FilePath),m_iOutputLevel(0) {}
			

			void SetOutputLevel(const LOGLevel __VSNC_IN level) noexcept override;
			/**
			 * @brief 日志输出
			 * @param level 日志等级
			 * @param ptrLogEvent 日志事件指针
			*/
			void Log(const LOGLevel __VSNC_IN level, LogEventPtr __VSNC_IN ptrLogEvent) noexcept override;
			/**
			 * @brief Trace日志输出
			 * @param ptrLogEvent 日志事件指针
			*/
			void Trace(LogEventPtr  __VSNC_IN ptrLogEvent) noexcept override;
			/**
			 * @brief Debug日志输出
			 * @param ptrLogEvent 日志事件指针
			*/
			void Debug(LogEventPtr  __VSNC_IN ptrLogEvent) noexcept override;
			/**
			 * @brief Info日志输出
			 * @param ptrLogEvent 日志事件指针
			*/
			void Info(LogEventPtr   __VSNC_IN ptrLogEvent) noexcept override;
			/**
			 * @brief Warn日志输出
			 * @param ptrLogEvent 日志事件指针
			*/
			void Warn(LogEventPtr   __VSNC_IN ptrLogEvent) noexcept override;
			/**
			 * @brief Error日志输出
			 * @param ptrLogEvent 日志事件指针
			*/
			void Error(LogEventPtr  __VSNC_IN ptrLogEvent) noexcept override;
			/**
			 * @brief Fatal日志输出
			 * @param ptrLogEvent 日志事件指针
			*/
			void Fatal(LogEventPtr  __VSNC_IN ptrLogEvent) noexcept override;
		private:
			/**
			 * @brief 日志器名称
			*/
			std::string m_sLoggerName;
			/**
			 * @brief 是否打印标志
			*/
			bool        m_bPrintFlag;
			/**
			 * @brief 是否是否写入文件标志
			*/
			bool        m_bWriteFlag;
			/**
			 * @brief 写入文件路径
			*/
			std::string m_sFilePath;
			
			/**
			 * @brief 输出等级
			*/
			size_t      m_iOutputLevel;
		};

		/**
		 * @brief 日志管理器实现
		*/
		class LoggerManagerIMPL final : public LoggerManager
		{
		public:
			/**
			 * @brief 构造函数
			 * @param loggerName 日志器名称  
			*/
			LoggerManagerIMPL(const std::string& __VSNC_IN loggerName);
			
			/**
			 * @brief 创建日志器
			 * @param name 日志器名称
			 * @param printFlag 是否打印标志
			 * @param writeFlag 是否写入文件标志
			 * @param filePath 文件路径，只有writeFlag为true才会写入
			 * @return 成功返回日志器指针,错误返回空指针（所以必须返回时必须先判断是否为空指针）
			*/
			LoggerPtr              CreateLoggerPtr(const std::string& __VSNC_IN name, const bool __VSNC_IN printFlag = true, const bool __VSNC_IN writeFlag = false, const std::string& __VSNC_IN filePath = "") noexcept override;
			
			/**
			 * @brief 删除日志器
			 * @param loggerName 日志器名称
			 * @return 成功返回true,错误返回false,如果日志器列表里没有就返回false
			*/
			bool                   Delete(const std::string& __VSNC_IN loggerName)       noexcept override;
			
			/**
			 * @brief 获取日志器名称列表
			 * @return 日志器名称列表
			*/
			std::list<std::string> GetListLoggerName()                                   noexcept override;
			
			/**
			 * @brief 获取子日志器指针
			 * @param loggerName 子日志器名称
			 * @return 子日志器指针
			*/
			LoggerPtr              GetLoggerPtr(const std::string& __VSNC_IN loggerName) noexcept override;
			
			/**
			 * @brief 获取主日志器指针
			 * @return 主日志器指针
			*/
			LoggerPtr              GetLoggerRootPtr()                                    noexcept override;
		private:
			/**
			 * @brief 创建日志器
			 * @param loggerParam 日志器参数 
			 * @return 成功返回日志器指针,错误返回空指针
			*/
			LoggerPtr              __create_logger_ptr(const LoggerParam& loggerParam)   noexcept;
		private:
			/**
			 * @brief 主日志器
			*/
			LoggerPtr   m_pRootLogger;
			/**
			 * @brief 非法日志器
			*/
			LoggerPtr   m_pIllegalLogger;
			/**
			 * @brief 日志器锁
			*/
			std::mutex  m_mtxLogger;
			/**
			 * @brief 日志器列表
			*/
			std::list<std::string> m_lstLoggerName;
			/**
			 * @brief 日志器列表
			*/
			std::map<std::string, LoggerPtr> m_mapLoggers;
		};
	}
}





#endif // !__VSNC_LOG_IMPL_H__

