#include "vsnc_log_impl.h"
#include "../files/vsnc_files.h"
using namespace vsnc::log;

namespace vsnc
{
    namespace log
    {
        /**
         * @brief �Ƿ���־����������û�д�����־��������ʹ���������־��ʱ��Ӵ���־����ӡ
        */
        static const char* VSNC_LOG_ILLEGAL_NAME = "illegal";
        /**
         * @brief ����־����������û�д�����־��������ʹ���������־��ʱ��Ӵ���־����ӡ
        */
        static const char* VSNC_LOG_ROOT_NAME = "root";

        /**
         * @brief ����
         * @param ss ����Ĺ�����
         * @param num ����
         * @param head ǰ�油�ַ���
         * @param tail ĩβ���ַ���
         * @param digits λ��
        */
        static void __zero(std::stringstream& __VSNC_IN_OUT ss, const int __VSNC_IN num, const std::string& head = "", const std::string& tail = "", const int __VSNC_IN digits = 2) noexcept;

        /**
         * @brief �ַ���ת�ȼ�ö��
         * @param level �ȼ�ö��
         * @return �ȼ��ַ���
        */
        static std::string __level_to_string(const LOGLevel __VSNC_IN level);

        /**
         * @brief �ַ���ת�ȼ�ö��
         * @param strLevel �ȼ��ַ���
         * @return �ȼ�ö��
        */
        static LOGLevel    __level_from_string(const std::string& __VSNC_IN strLevel);

        /**
         * @brief ��ȡʱ���ʽ
         * @param timestamp ʱ���
         * @return ��ʽ��ʱ��
        */
        static std::string __get_time_format(const int64_t __VSNC_IN timestamp);

        /**
         * @brief ��ȡ�ļ���
         * @param fileName �ļ�·��
         * @return �ļ���
        */
        static std::string __get_filename_last(const std::string& __VSNC_IN fileName);

       
    }
}

void vsnc::log::__zero(std::stringstream& __VSNC_IN_OUT ss, const int __VSNC_IN num, const std::string& head, const std::string& tail, const int __VSNC_IN digits) noexcept
{
    auto __digist = (digits - 1) * 10;
    auto __num = num;
    ss << head;
    while (__num < __digist)
    {
        ss << "0";
        __num *= 10;
    }
    ss << num << tail;
}

std::string vsnc::log::__level_to_string(const LOGLevel __VSNC_IN level)
{
#ifdef __VSNC_TEST
    //�ⷽ��Ҫ�������������ֶ��޸ģ�������
#define TOLOG(name) if(LOGLevel::name == level) return #name;
    TOLOG(LOG_TRACE);
    TOLOG(LOG_DEBUG);
    TOLOG(LOG_INFO);
    TOLOG(LOG_WARN);
    TOLOG(LOG_ERROR);
    TOLOG(LOG_FATAL);
    return "UNKNOW";
#undef TOLOG
#else
    if (LOGLevel::LOG_TRACE == level) return "LOG_TRACE";
    if (LOGLevel::LOG_DEBUG == level) return "LOG_DEBUG";
    if (LOGLevel::LOG_INFO == level) return "LOG_INFO";
    if (LOGLevel::LOG_WARN == level) return "LOG_WARN";
    if (LOGLevel::LOG_ERROR == level) return "LOG_ERROR";
    if (LOGLevel::LOG_FATAL == level) return "LOG_FATAL";
    return "UNKNOW";
#endif // __VSNC_TEST
}

LOGLevel vsnc::log::__level_from_string(const std::string& __VSNC_IN strLevel)
{
#define TOLOG(level, v) if(strLevel == #v) { return LOGLevel::level; }
    TOLOG(LOG_TRACE, trace);
    TOLOG(LOG_DEBUG, debug);
    TOLOG(LOG_INFO, info);
    TOLOG(LOG_WARN, warn);
    TOLOG(LOG_ERROR, error);
    TOLOG(LOG_FATAL, fatal);

    TOLOG(LOG_TRACE, TRACE);
    TOLOG(LOG_DEBUG, DEBUG);
    TOLOG(LOG_INFO, INFO);
    TOLOG(LOG_WARN, WARN);
    TOLOG(LOG_ERROR, ERROR);
    TOLOG(LOG_FATAL, FATAL);
    return LOGLevel::LOG_UNKNOW;
#undef TOLOG
}

std::string vsnc::log::__get_time_format(const int64_t __VSNC_IN timestamp)
{
    if (timestamp == 0) return "[0]";
    int ms = timestamp % 1000;//ȡ����
    time_t tick = (time_t)(timestamp / 1000);//ת��ʱ��
    struct tm now;
    localtime_s(&now, &tick);
    std::stringstream ss;
    __zero(ss, now.tm_year + 1900, "[");
    __zero(ss, now.tm_mon, "-");
    __zero(ss, now.tm_mday, "-");
    __zero(ss, now.tm_hour, " ");
    __zero(ss, now.tm_min, ":");
    __zero(ss, now.tm_sec, ":");
    __zero(ss, ms, ".", "]");
    return ss.str();
}


std::string vsnc::log::__get_filename_last(const std::string& __VSNC_IN fileName)
{
    auto num = fileName.rfind("\\");
    if (num == std::string::npos)  return fileName;
    return fileName.substr(num + 1);
}

vsnc::log::LogEventIMPL::~LogEventIMPL()
{
    //std::cout << "����" << std::endl;
}

std::string vsnc::log::LogEventIMPL::GetFormat(const std::string& __VSNC_IN loggerName, const LOGLevel __VSNC_IN level) noexcept
{

    m_cParam;
    // ʱ��
    std::stringstream ss;
    // ��־����
    ss << "[" + loggerName + "]";
    // ��ǰʱ���
    ss << __get_time_format(m_cParam.Timestamp);
    // �߳�
    ss << "[P:" << m_cParam.ProccessID << "/T:" << m_cParam.ThreadID << "]";
    // �ļ� ����
    ss << "[" << __get_filename_last(m_cParam.FileName) << ":" << m_cParam.Line << "]";
    // ��־�ȼ�
    ss << "[" << __level_to_string(level) << "]";
    // �������ʱ��
    ss << "[" << m_cParam.Elapse << "]";
    // ��־����
    ss << m_cParam.Content;
    return ss.str();
}


void vsnc::log::LoggerIMPL::SetOutputLevel(const LOGLevel level) noexcept
{
    m_iOutputLevel = static_cast<size_t>(level);
}

void LoggerIMPL::Log(const LOGLevel __VSNC_IN level, LogEventPtr __VSNC_IN ptrLogEvent) noexcept
{

    std::string strLogEventParam = ptrLogEvent->GetFormat(m_sLoggerName, level);
    if (static_cast<size_t>(level) >= m_iOutputLevel)
    {
        if (m_bPrintFlag) std::cout << strLogEventParam << std::endl;
        if (m_bWriteFlag) vsnc::utils::VFile::WriteString(m_sFilePath, strLogEventParam + "\n");
    }
}

void LoggerIMPL::Trace(LogEventPtr __VSNC_IN ptrLogEvent) noexcept
{
    Log(LOGLevel::LOG_TRACE, ptrLogEvent);
}

void LoggerIMPL::Debug(LogEventPtr __VSNC_IN ptrLogEvent) noexcept
{
    Log(LOGLevel::LOG_TRACE, ptrLogEvent);
}

void LoggerIMPL::Info(LogEventPtr __VSNC_IN ptrLogEvent) noexcept
{
    Log(LOGLevel::LOG_INFO, ptrLogEvent);
}

void LoggerIMPL::Warn(LogEventPtr __VSNC_IN ptrLogEvent) noexcept
{
    Log(LOGLevel::LOG_WARN, ptrLogEvent);
}

void LoggerIMPL::Error(LogEventPtr __VSNC_IN ptrLogEvent) noexcept
{
    Log(LOGLevel::LOG_ERROR, ptrLogEvent);
}

void LoggerIMPL::Fatal(LogEventPtr __VSNC_IN ptrLogEvent) noexcept
{
    Log(LOGLevel::LOG_FATAL, ptrLogEvent);
}

LoggerManagerIMPL::LoggerManagerIMPL(const std::string& __VSNC_IN loggerName)
{
    auto __loggerName = loggerName;
    if (__loggerName.empty()) __loggerName = VSNC_LOG_ROOT_NAME;
    m_pRootLogger = std::make_shared<LoggerIMPL>(LoggerParam({ __loggerName, true, true, "vsnc_log\\vsnc_log.txt" }));
    m_pIllegalLogger = std::make_shared<LoggerIMPL>(LoggerParam({ VSNC_LOG_ILLEGAL_NAME, true, true, "vsnc_log\\vsnc_log.txt" }));
}

LoggerPtr LoggerManagerIMPL::CreateLoggerPtr(const std::string& __VSNC_IN name, const bool __VSNC_IN printFlag, const bool __VSNC_IN writeFlag, const std::string& __VSNC_IN filePath) noexcept
{
    return __create_logger_ptr(LoggerParam({ name,printFlag,writeFlag,filePath }));
}

bool LoggerManagerIMPL::Delete(const std::string& __VSNC_IN loggerName) noexcept
{
    std::lock_guard<std::mutex> lock(m_mtxLogger);
    if (m_mapLoggers.find(loggerName) != m_mapLoggers.end())
    {
        //�������,��ɾ����
        m_mapLoggers.erase(loggerName);
        m_lstLoggerName.remove(loggerName);
        return true;
    }
    return false;
}

std::list<std::string> LoggerManagerIMPL::GetListLoggerName() noexcept
{
    std::lock_guard<std::mutex> lock(m_mtxLogger);
    return m_lstLoggerName;
}

LoggerPtr LoggerManagerIMPL::GetLoggerPtr(const std::string& __VSNC_IN loggerName) noexcept
{
    std::lock_guard<std::mutex> lock(m_mtxLogger);
    if (loggerName.empty()) return m_pRootLogger;
    if (m_mapLoggers.find(loggerName) != m_mapLoggers.end())
    {
        //����Ѿ�����
        return m_mapLoggers.at(loggerName);
    }
    return m_pIllegalLogger;
}

LoggerPtr vsnc::log::LoggerManagerIMPL::GetLoggerRootPtr() noexcept
{
    return m_pRootLogger;
}

LoggerPtr vsnc::log::LoggerManagerIMPL::__create_logger_ptr(const LoggerParam& loggerParam) noexcept
{
    if (loggerParam.Name == VSNC_LOG_ROOT_NAME) return m_pRootLogger;
    if (loggerParam.Name == VSNC_LOG_ILLEGAL_NAME) return m_pRootLogger;
    std::lock_guard<std::mutex> lock(m_mtxLogger);
    if (m_mapLoggers.find(loggerParam.Name) != m_mapLoggers.end())
    {
        //����Ѿ����ڣ�ֱ�ӷ��أ�����Ҫ���롣
        return m_mapLoggers.at(loggerParam.Name);
    }
    //�����ھʹ���
    LoggerPtr ptrLogger = std::make_shared<LoggerIMPL>(loggerParam);
    if (ptrLogger.get() != nullptr)
    {
        m_lstLoggerName.push_back(loggerParam.Name);
        m_mapLoggers.insert(std::pair<std::string, LoggerPtr>(loggerParam.Name, ptrLogger));
        return ptrLogger;
    }
    return m_pRootLogger;
}
