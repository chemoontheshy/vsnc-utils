#include "vsnc_logger.h"
#include "vsnc_log_impl.h"
#include "vsnc_logger.h"
using namespace vsnc::log;


vsnc::log::InstanceMgr::InstanceMgr() :m_pLoggerMgr(std::make_shared<LoggerManagerIMPL>(""))
{

}

LogEventPtr vsnc::log::CreateLogEventPtr(const LOGEventParam& __VSNC_IN logEventParam)
{
	return LogEventPtr(new LogEventIMPL(logEventParam));
}
