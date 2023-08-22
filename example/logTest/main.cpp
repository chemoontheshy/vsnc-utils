#include <iostream>
#include "common_utils.h"

int main()
{
	VSNC_GET_ALL_CREATE("hskj", "hskj_log\\hskj_log.txt");
	//VSNC_SET_OUTPUT_LEVLE("hskj", 5);
	VSNC_LOG_TRACE("hskj", "TRACE");
	VSNC_LOG_DEBUG("hskj", "DEBUG");
	VSNC_LOG_INFO("hskj", "INFO");
	VSNC_LOG_WARN("hskj", "WARN");
	VSNC_LOG_ERROR("hskj", "ERROR");
	VSNC_LOG_FATAL("hskj", "FATAL");
	return 0;
}