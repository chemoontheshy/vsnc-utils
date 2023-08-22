#include "vsnc_log_impl.h"
#include "../files/vsnc_files.h"
using namespace vsnc::log;

namespace vsnc
{
    namespace log
    {
        /**
         * @brief 非法日志器。当出现没有创建日志器，但是使用了相关日志器时会从此日志器打印
        */
        static const char* VSNC_LOG_ILLEGAL_NAME = "illegal";
        /**
         * @brief 主日志器。当出现没有创建日志器，但是使用了相关日志器时会从此日志器打印
        */
        static const char* VSNC_LOG_ROOT_NAME = "root";

        /**
         * @brief 补零
         * @param ss 输入的构造器
         * @param num 数字
         * @param head 前面补字符串
         * @param tail 末尾补字符串
         * @param digits 位数
        */
        static void __zero(std::stringstream& __VSNC_IN_OUT ss, const int __VSNC_IN num, const std::string& head = "", const std::string& tail = "", const int __VSNC_IN digits = 2) noexcept;

        /**
         * @brief 字符串转等级枚举
         * @param level 等级枚举
         * @return 等级字符串
        */
        static std::string __level_to_string(const LOGLevel __VSNC_IN level);

        /**
         * @brief 字符串转等级枚举
         * @param strLevel 等级字符串
         * @return 等级枚举
        */
        static LOGLevel    __level_from_string(const std::string& __VSNC_IN strLevel);

        /**
         * @brief 获取时间格式
         * @param timestamp 时间戳
         * @return 格式化时间
        */
        static std::string __get_time_format(const int64_t __VSNC_IN timestamp);

        /**
         * @brief 获取文件名
         * @param fileName 文件路径
         * @return 文件名
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
    //这方法要是重命名还得手动修改，不方便
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
    int ms = timestamp % 1000;//取毫秒
    time_t tick = (time_t)(timestamp / 1000);//转换时间
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
    //std::cout << "析构" << std::endl;
}

std::string vsnc::log::LogEventIMPL::GetFormat(const std::string& __VSNC_IN loggerName, const LOGLevel __VSNC_IN level) noexcept
{

    m_cParam;
    // 时间
    std::stringstream ss;
    // 日志名字
    ss << "[" + loggerName + "]";
    // 当前时间戳
    ss << __get_time_format(m_cParam.Timestamp);
    // 线程
    ss << "[P:" << m_cParam.ProccessID << "/T:" << m_cParam.ThreadID << "]";
    // 文件 行数
    ss << "[" << __get_filename_last(m_cParam.FileName) << ":" << m_cParam.Line << "]";
    // 日志等级
    ss << "[" << __level_to_string(level) << "]";
    // 经过多久时间
    ss << "[" << m_cParam.Elapse << "]";
    // 日志内容
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
        //如果存在,就删除。
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
        //如果已经存在
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
        //如果已经存在，直接返回，不需要插入。
        return m_mapLoggers.at(loggerParam.Name);
    }
    //不存在就创建
    LoggerPtr ptrLogger = std::make_shared<LoggerIMPL>(loggerParam);
    if (ptrLogger.get() != nullptr)
    {
        m_lstLoggerName.push_back(loggerParam.Name);
        m_mapLoggers.insert(std::pair<std::string, LoggerPtr>(loggerParam.Name, ptrLogger));
        return ptrLogger;
    }
    return m_pRootLogger;
}
