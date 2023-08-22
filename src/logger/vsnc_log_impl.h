#ifndef __VSNC_LOGGER_IMPL_H__
#define __VSNC_LOGGER_IMPL_H__
#include "vsnc_logger.h"
#include <mutex>


namespace vsnc
{
	namespace log
	{
		/**
		 * @brief ��־�¼�ʵ��
		*/
		class LogEventIMPL final : public LogEvent
		{
		public:
			
			/**
			 * @brief ���캯��
			 * @param param ��־����
			*/
			LogEventIMPL(const LOGEventParam& __VSNC_IN param) :m_cParam(param) {}

			/*
			* ��������
			*/
			~LogEventIMPL();
			
			/**
			 * @brief ���ļ���ʽ
			 * @param loggerName �ļ���
			 * @param level ��־�ȼ�
			 * @return ����ļ���ʽ����ַ���
			*/
			std::string GetFormat(const std::string& __VSNC_IN loggerName, const LOGLevel __VSNC_IN level) noexcept;
		private:
			/**
			 * @brief ��־����
			*/
			LOGEventParam     m_cParam;
		};

		/**
		 * @brief ��־��ʵ��
		*/
		class LoggerIMPL final : public Logger
		{
		public:
			/**
			 * @brief ���캯��
			 * @param loggerParam ��־���� 
			*/
			LoggerIMPL(const LoggerParam& __VSNC_IN loggerParam) :m_sLoggerName(loggerParam.Name), m_bPrintFlag(loggerParam.PrintFlag),
				m_bWriteFlag(loggerParam.WriteFlag), m_sFilePath(loggerParam.FilePath),m_iOutputLevel(0) {}
			

			void SetOutputLevel(const LOGLevel __VSNC_IN level) noexcept override;
			/**
			 * @brief ��־���
			 * @param level ��־�ȼ�
			 * @param ptrLogEvent ��־�¼�ָ��
			*/
			void Log(const LOGLevel __VSNC_IN level, LogEventPtr __VSNC_IN ptrLogEvent) noexcept override;
			/**
			 * @brief Trace��־���
			 * @param ptrLogEvent ��־�¼�ָ��
			*/
			void Trace(LogEventPtr  __VSNC_IN ptrLogEvent) noexcept override;
			/**
			 * @brief Debug��־���
			 * @param ptrLogEvent ��־�¼�ָ��
			*/
			void Debug(LogEventPtr  __VSNC_IN ptrLogEvent) noexcept override;
			/**
			 * @brief Info��־���
			 * @param ptrLogEvent ��־�¼�ָ��
			*/
			void Info(LogEventPtr   __VSNC_IN ptrLogEvent) noexcept override;
			/**
			 * @brief Warn��־���
			 * @param ptrLogEvent ��־�¼�ָ��
			*/
			void Warn(LogEventPtr   __VSNC_IN ptrLogEvent) noexcept override;
			/**
			 * @brief Error��־���
			 * @param ptrLogEvent ��־�¼�ָ��
			*/
			void Error(LogEventPtr  __VSNC_IN ptrLogEvent) noexcept override;
			/**
			 * @brief Fatal��־���
			 * @param ptrLogEvent ��־�¼�ָ��
			*/
			void Fatal(LogEventPtr  __VSNC_IN ptrLogEvent) noexcept override;
		private:
			/**
			 * @brief ��־������
			*/
			std::string m_sLoggerName;
			/**
			 * @brief �Ƿ��ӡ��־
			*/
			bool        m_bPrintFlag;
			/**
			 * @brief �Ƿ��Ƿ�д���ļ���־
			*/
			bool        m_bWriteFlag;
			/**
			 * @brief д���ļ�·��
			*/
			std::string m_sFilePath;
			
			/**
			 * @brief ����ȼ�
			*/
			size_t      m_iOutputLevel;
		};

		/**
		 * @brief ��־������ʵ��
		*/
		class LoggerManagerIMPL final : public LoggerManager
		{
		public:
			/**
			 * @brief ���캯��
			 * @param loggerName ��־������  
			*/
			LoggerManagerIMPL(const std::string& __VSNC_IN loggerName);
			
			/**
			 * @brief ������־��
			 * @param name ��־������
			 * @param printFlag �Ƿ��ӡ��־
			 * @param writeFlag �Ƿ�д���ļ���־
			 * @param filePath �ļ�·����ֻ��writeFlagΪtrue�Ż�д��
			 * @return �ɹ�������־��ָ��,���󷵻ؿ�ָ�루���Ա��뷵��ʱ�������ж��Ƿ�Ϊ��ָ�룩
			*/
			LoggerPtr              CreateLoggerPtr(const std::string& __VSNC_IN name, const bool __VSNC_IN printFlag = true, const bool __VSNC_IN writeFlag = false, const std::string& __VSNC_IN filePath = "") noexcept override;
			
			/**
			 * @brief ɾ����־��
			 * @param loggerName ��־������
			 * @return �ɹ�����true,���󷵻�false,�����־���б���û�оͷ���false
			*/
			bool                   Delete(const std::string& __VSNC_IN loggerName)       noexcept override;
			
			/**
			 * @brief ��ȡ��־�������б�
			 * @return ��־�������б�
			*/
			std::list<std::string> GetListLoggerName()                                   noexcept override;
			
			/**
			 * @brief ��ȡ����־��ָ��
			 * @param loggerName ����־������
			 * @return ����־��ָ��
			*/
			LoggerPtr              GetLoggerPtr(const std::string& __VSNC_IN loggerName) noexcept override;
			
			/**
			 * @brief ��ȡ����־��ָ��
			 * @return ����־��ָ��
			*/
			LoggerPtr              GetLoggerRootPtr()                                    noexcept override;
		private:
			/**
			 * @brief ������־��
			 * @param loggerParam ��־������ 
			 * @return �ɹ�������־��ָ��,���󷵻ؿ�ָ��
			*/
			LoggerPtr              __create_logger_ptr(const LoggerParam& loggerParam)   noexcept;
		private:
			/**
			 * @brief ����־��
			*/
			LoggerPtr   m_pRootLogger;
			/**
			 * @brief �Ƿ���־��
			*/
			LoggerPtr   m_pIllegalLogger;
			/**
			 * @brief ��־����
			*/
			std::mutex  m_mtxLogger;
			/**
			 * @brief ��־���б�
			*/
			std::list<std::string> m_lstLoggerName;
			/**
			 * @brief ��־���б�
			*/
			std::map<std::string, LoggerPtr> m_mapLoggers;
		};
	}
}





#endif // !__VSNC_LOG_IMPL_H__

