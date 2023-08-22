#include "common_utils.h"
#include "files/vsnc_files.h"
#include "logger/vsnc_logger.h"


static vsnc::log::LOGLevel __get_level(const int level)
{
	vsnc::log::LOGLevel tempLevel = vsnc::log::LOGLevel::LOG_UNKNOW;
	if (level == 1) tempLevel = vsnc::log::LOGLevel::LOG_TRACE;
	if (level == 2) tempLevel = vsnc::log::LOGLevel::LOG_DEBUG;
	if (level == 3) tempLevel = vsnc::log::LOGLevel::LOG_INFO;
	if (level == 4) tempLevel = vsnc::log::LOGLevel::LOG_WARN;
	if (level == 5) tempLevel = vsnc::log::LOGLevel::LOG_ERROR;
	if (level == 6) tempLevel = vsnc::log::LOGLevel::LOG_FATAL;
	return tempLevel;
}


bool vsnc::utils::mkdir(const char* filename)
{
	return vsnc::utils::VFile::Mkdir(filename);
}

bool vsnc::utils::rm(const char* path)
{
	return vsnc::utils::VFile::Rm(path);
}


bool vsnc::utils::copy(const char* from, const char* to, const bool flag)
{
	return vsnc::utils::VFile::Copy(from, to, false);
}

bool vsnc::utils::get_real_path(const char* path, char* __VSNC_OUT rpath)
{
	std::string rPath;
	if (vsnc::utils::VFile::GetRealpath(path, rPath))
	{
		memcpy(rpath, rPath.c_str(), rPath.size());
		return true;
	}
	return false;
}

bool vsnc::utils::get_dir_name(const char* inFileName, char* __VSNC_OUT outFile)
{
	std::string filename = vsnc::utils::VFile::GetDirname(inFileName);
	memcpy(outFile, filename.c_str(), filename.size());
	return true;
}

bool vsnc::utils::get_base_name(const char* inFileName, char* __VSNC_OUT outFile)
{
	std::string filename = vsnc::utils::VFile::GetBasename(inFileName);
	memcpy(outFile, filename.c_str(), filename.size());
	return true;
}

bool vsnc::utils::write_string(const char* filename, const char* context)
{
	return vsnc::utils::VFile::WriteString(filename, context);
}

bool vsnc::utils::write_stream(const char* filename, char* data, const int length)
{
	return vsnc::utils::VFile::WriteStream(filename, reinterpret_cast<uint8_t*>(data), static_cast<size_t>(length));
}

bool vsnc::utils::create_logger(const char* name, const bool printFlag, const bool writeFlag, const char* filePath, const int level)
{
	auto logPtr = vsnc::log::SingleLogMgr::GetInstance()->GetLoggerMgr()->CreateLoggerPtr(name, printFlag, writeFlag, filePath);
	if (logPtr)
	{
		logPtr->SetOutputLevel(__get_level(level));
		return true;
	}
	return false;
}

bool vsnc::utils::delete_logger(const char* name)
{
	return vsnc::log::SingleLogMgr::GetInstance()->GetLoggerMgr()->Delete(name);
}



void vsnc::utils::set_output_level(const char* name, const int level)
{
	vsnc::log::SingleLogMgr::GetInstance()->GetLoggerMgr()->GetLoggerPtr(name)->SetOutputLevel(__get_level(level));
}

void vsnc::utils::vsnc_log(const char* name, const int level, const char* file, const int64_t line, int64_t elapse, int64_t timestamp, size_t pid, size_t tid, const char* content)
{
	auto eventPtr = vsnc::log::CreateLogEventPtr(vsnc::log::LOGEventParam({ file, line,elapse, timestamp, pid, tid,content }));
	vsnc::log::SingleLogMgr::GetInstance()->GetLoggerMgr()->GetLoggerPtr(name)->Log(__get_level(level), eventPtr);
}

void vsnc::utils::vsnc_root_log(const char* name, const int level, const char* file, const int64_t line, int64_t elapse, int64_t timestamp, size_t pid, size_t tid, const char* content)
{
	auto eventPtr = vsnc::log::CreateLogEventPtr(vsnc::log::LOGEventParam({ file, line,elapse, timestamp, pid, tid,content }));
	vsnc::log::SingleLogMgr::GetInstance()->GetLoggerMgr()->GetLoggerRootPtr()->Log(__get_level(level), eventPtr);
}
