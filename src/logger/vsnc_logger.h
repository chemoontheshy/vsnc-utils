#ifndef __VSNC_LOGGER_H__
#define __VSNC_LOGGER_H__
#include "../vsnc_utils.h"
#include <map>

namespace vsnc
{
	namespace log
	{
		/**
		 * @brief ��־�ȼ�
		*/
		enum class LOGLevel : size_t
		{
			/**
			 * @brief δ֪�ȼ�
			*/
			LOG_UNKNOW,
			/**
			 * @brief ׷�ٵȼ�
			*/
			LOG_TRACE,
			/**
			 * @brief ָ��ϸ������Ϣ�¼��Ե���Ӧ�ó����Ƿǳ��а����ģ���Ҫ���ڿ��������д�ӡһЩ������Ϣ��
			*/
			LOG_DEBUG,
			/**
			 * @brief ��Ϣ�ڴ����ȼ�����ͻ��ǿ��Ӧ�ó�������й��̡���ӡһЩ�����Ȥ�Ļ�����Ҫ����Ϣ���������������������������������е�һЩ��Ҫ��Ϣ�����ǲ������ã������ӡ�������־��
			*/
			LOG_INFO,
			/**
			 * @brief ���������Ǳ�ڴ�������Σ���Щ��Ϣ���Ǵ�����Ϣ������ҲҪ������Ա��һЩ��ʾ��
			*/
			LOG_WARN,
			/**
			 * @brief ָ����Ȼ���������¼�������Ȼ��Ӱ��ϵͳ�ļ������С���ӡ������쳣��Ϣ������������̫�����־������ʹ���������
			*/
			LOG_ERROR,
			/**
			 * @brief ָ��ÿ�����صĴ����¼����ᵼ��Ӧ�ó�����˳����������Ƚϸ��ˡ��ش�������ּ��������ֱ��ֹͣ������
			*/
			LOG_FATAL,
		};


		/**
		 * @brief LOG��־��ʽ
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
		 * @brief ��־�¼�����
		*/
		struct LOGEventParam
		{
			/**
			 * @brief �ļ���
			*/
			std::string FileName;
			/**
			 * @brief ����
			*/
			int64_t     Line;
			/**
			 * @brief  ����ʱ�侭��ʱ�䣨���룩
			*/
			int64_t     Elapse;
			/**
			 * @brief  ��ǰʱ��ʱ���
			*/
			int64_t     Timestamp;
			/**
			 * @brief ����ID
			*/
			size_t      ProccessID;
			/**
			 * @brief �߳�ID
			*/
			size_t      ThreadID;
			/**
			 * @brief ����
			*/
			std::string Content;
		};

		/**
		 * @brief ��־������
		*/
		struct LoggerParam
		{
			/**
			 * @brief ��־����
			*/
			std::string Name;
			/**
			 * @brief ��ӡ��־
			*/
			bool        PrintFlag;
			/**
			 * @brief д���ļ���־
			*/
			bool        WriteFlag;
			/**
			 * @brief д���ļ�·��
			*/
			std::string FilePath;
		};

		/**
		 * @brief ��־�¼�
		*/
		class LogEvent
		{
		public:
			~LogEvent() = default;

			/**
			 * @brief ���ļ���ʽ 
			 * @param loggerName �ļ��� 
			 * @param level ��־�ȼ�
			 * @return ����ļ���ʽ����ַ���
			*/
			virtual std::string GetFormat(const std::string& __VSNC_IN loggerName, const LOGLevel __VSNC_IN level) noexcept = 0;
		};

		using LogEventPtr = std::shared_ptr<LogEvent>;
		
		/**
		 * @brief ������־�¼�
		 * @param logEventParam ��־����
		 * @return ��־�¼�ָ��
		*/
		LogEventPtr CreateLogEventPtr(const LOGEventParam& __VSNC_IN logEventParam);

		/**
		 * @brief ��־������
		*/
		class Logger
		{
		public:
			/*
			* ��������
			*/
			~Logger() = default;


			/**
			 * @brief ��������ȼ�������ȼ�Ӧ�ÿ������ⲿ����
			 * @param  ����ȼ�
			*/
			virtual void SetOutputLevel(const LOGLevel __VSNC_IN level) noexcept = 0;

			/**
			 * @brief ��־���
			 * @param level ��־�ȼ�
			 * @param ptrLogEvent ��־�¼�ָ��
			*/
			virtual void Log(const LOGLevel __VSNC_IN level, LogEventPtr __VSNC_IN ptrLogEvent) noexcept = 0;

			/**
			 * @brief Trace��־���
			 * @param ptrLogEvent ��־�¼�ָ��
			*/
			virtual void Trace(LogEventPtr  __VSNC_IN ptrLogEvent) noexcept = 0;

			/**
			 * @brief Debug��־���
			 * @param ptrLogEvent ��־�¼�ָ��
			*/
			virtual void Debug(LogEventPtr  __VSNC_IN ptrLogEvent) noexcept = 0;

			/**
			 * @brief Info��־���
			 * @param ptrLogEvent ��־�¼�ָ��
			*/
			virtual void Info(LogEventPtr   __VSNC_IN ptrLogEvent) noexcept = 0;

			/**
			 * @brief Warn��־���
			 * @param ptrLogEvent ��־�¼�ָ��
			*/
			virtual void Warn(LogEventPtr   __VSNC_IN ptrLogEvent) noexcept = 0;

			/**
			 * @brief Error��־���
			 * @param ptrLogEvent ��־�¼�ָ��
			*/
			virtual void Error(LogEventPtr  __VSNC_IN ptrLogEvent) noexcept = 0;

			/**
			 * @brief Fatal��־���
			 * @param ptrLogEvent ��־�¼�ָ��
			*/
			virtual void Fatal(LogEventPtr  __VSNC_IN ptrLogEvent) noexcept = 0;
		};
		/**
		 * @brief ָ������
		*/
		using LoggerPtr = std::shared_ptr<Logger>;


		/**
		 * @brief ��־������
		*/
		class LoggerManager
		{
		public:
			/**
			 * @brief ��������
			*/
			~LoggerManager() = default;

			/**
			 * @brief ������־��
			 * @param name ��־������
			 * @param printFlag �Ƿ��ӡ��־
			 * @param writeFlag �Ƿ�д���ļ���־
			 * @param filePath �ļ�·����ֻ��writeFlagΪtrue�Ż�д��
			 * @return �ɹ�������־��ָ��,���󷵻ؿ�ָ�루���Ա��뷵��ʱ�������ж��Ƿ�Ϊ��ָ�룩
			*/
			virtual LoggerPtr              CreateLoggerPtr(const std::string& __VSNC_IN name, const bool __VSNC_IN printFlag = true, const bool __VSNC_IN writeFlag = false, const std::string& __VSNC_IN filePath = "") noexcept = 0;

			/**
			 * @brief ɾ����־��
			 * @param loggerName ��־������
			 * @return �ɹ�����true,���󷵻�false,�����־���б���û�оͷ���false
			*/
			virtual bool                   Delete(const std::string& __VSNC_IN loggerName)       noexcept = 0;


			/**
			 * @brief ��ȡ��־�������б�
			 * @return ��־�������б�
			*/
			virtual std::list<std::string> GetListLoggerName()                                   noexcept = 0;

			/**
			 * @brief ��ȡ����־��ָ��
			 * @param loggerName ����־������
			 * @return ����־��ָ��
			*/
			virtual LoggerPtr              GetLoggerPtr(const std::string& __VSNC_IN loggerName) noexcept = 0;

			/**
			 * @brief ��ȡ����־��ָ��
			 * @return ����־��ָ��
			*/
			virtual LoggerPtr              GetLoggerRootPtr()                                    noexcept = 0;

		};

		/**
		 * @brief ָ������
		*/
		using   LoggerMgr = std::shared_ptr<LoggerManager>;

		/**
		 * @brief ʵ������־������������ʵ�ֵ���ģʽ
		*/
		class InstanceMgr
		{
		public:
			/**
			 * @brief ����
			*/
			InstanceMgr();

			/**
			 * @brief ��ȡ��־������ָ��
			 * @return ��־������ָ��
			*/
			LoggerMgr GetLoggerMgr() { return m_pLoggerMgr; }
		private:
			/**
			 * @brief ��־������ָ��
			*/
			LoggerMgr m_pLoggerMgr;
		};

		/**
		 * @brief ʵ��������
		*/
		typedef __VSNC_PORT vsnc::utils::SingletonPtr<InstanceMgr> SingleLogMgr;
	}
}
#endif // !__VSNC_LOGGER_H__