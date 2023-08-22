#include "vsnc_files.h"
#include <io.h>
#include <Windows.h>
#include <fstream>
#include <istream>


namespace vsnc
{
	namespace utils
	{
		static void __get_files(std::list<std::string>& files, std::list<std::string>& paths, std::string& path, const std::string& subfix) noexcept;

		static void __remove(std::string path) noexcept;

		static std::string __create_multiple_folders(std::string path) noexcept;

	}
}


void vsnc::utils::__get_files(std::list<std::string>& files, std::list<std::string>& paths, std::string& path, const std::string& subfix) noexcept
{
	//文件句柄
	intptr_t hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;

	std::string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之
			//如果不是,加入列表
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					__get_files(files, paths, p.assign(path).append("\\").append(fileinfo.name), subfix);
				paths.push_back(path);
			}
			else
			{
				std::string filename = fileinfo.name;
				if (subfix.empty())
				{
					files.push_back(p.assign(path).append("\\").append(filename));
				}
				else
				{
					if (filename.find(subfix) != std::string::npos)
					{
						files.push_back(p.assign(path).append("\\").append(filename));
					}
				}
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}


void vsnc::utils::__remove(std::string path) noexcept
{

	//文件句柄
	intptr_t hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;


	std::string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					p.assign(path).append("\\").append(fileinfo.name);
					__remove(p);
					if (!RemoveDirectoryA(p.c_str())) break;
				}
			}
			else
			{
				p.assign(path).append("\\").append(fileinfo.name);
				std::cout << p << std::endl;
				if (!DeleteFileA(p.c_str())) break;

			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

std::string vsnc::utils::__create_multiple_folders(std::string path) noexcept
{
	// 判断是否存在
	if (_access(path.c_str(), 0) == 0)
	{
		return path;
	}
	size_t length = path.find_last_of("\\");
	if (length == std::string::npos)
	{
		length = 0;
		char curPath[254];
		GetCurrentDirectoryA(254, curPath);
		path = "\\" + path;
		path = curPath + path;
		length = path.find_last_of("\\");
	}
	std::string parentDir = __create_multiple_folders(path.substr(0, length));
	std::string dirName = path.substr(length + 1);
	if (_access(path.c_str(), 0) != 0)
	{
		std::cout << dirName;

		CreateDirectoryA(dirName.c_str(), NULL);
	}
	return parentDir + "\\" + dirName;

}


void vsnc::utils::VFile::GetListAllFile(std::list<std::string>& __VSNC_OUT files, const std::string& __VSNC_IN path, const std::string& __VSNC_IN subfix) noexcept
{
	// 判断是否存在
	if (_access(path.c_str(), 0) != 0)
	{
		return;
	}
	std::string __path = path;
	std::list<std::string> paths;
	__get_files(files, paths, __path, subfix);
}

bool vsnc::utils::VFile::Mkdir(const char* __VSNC_IN dirname) noexcept
{
	// 判断是否存在
	if (_access(dirname, 0) != 0)
	{
		return CreateDirectoryA(dirname, NULL);
	}
	return true;
}

bool vsnc::utils::VFile::Rm(const char* __VSNC_IN path) noexcept
{
	// 判断是否存在
	if (_access(path, 0) == 0)
	{
		//文件句柄
		intptr_t hFile = 0;
		//文件信息
		struct _finddata_t fileinfo;
		std::string p;
		// 文件
		if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) == -1) return DeleteFileA(path);
		//文件夹

		__remove(path);
		return RemoveDirectoryA(path);
	}
	//文件不存在返回false
	return false;
}


bool vsnc::utils::VFile::Copy(const std::string& __VSNC_IN from, const std::string& __VSNC_IN to, const bool __VSNC_IN flag) noexcept
{
	// 判断是否存在
	if (_access(from.c_str(), 0) == 0)
	{
		//文件句柄
		intptr_t hFile = 0;
		//文件信息
		struct _finddata_t fileinfo;
		std::string p;
		// 文件
		if ((hFile = _findfirst(p.assign(from).append("\\*").c_str(), &fileinfo)) == -1)
		{
			// 如果是不存在的文件夹，也创建相关路径
			size_t length = to.find_last_of("\\");
			if (length != std::string::npos)
			{
				std::string __path = to.substr(0, length);
				__create_multiple_folders(__path);
			}
			return CopyFileA(from.c_str(), to.c_str(), flag);
		}
		//文件夹
		std::string __path = from;
		std::list<std::string> files;
		std::list<std::string> paths;
		__get_files(files, paths, __path, "");
		//排序去重
		paths.sort();
		paths.unique();
		//创建新的文件夹
		for (auto path : paths)
		{
			std::string newPath;
			newPath = to + path.substr(from.size());
			CreateDirectoryA(newPath.c_str(), nullptr);
		}
		for (auto file : files)
		{
			std::string newFile;
			newFile = to + file.substr(from.size());
			if (!CopyFileA(file.c_str(), newFile.c_str(), flag)) return false;
		}
		return true;
	}
	//文件不存在返回false
	return false;
}

bool vsnc::utils::VFile::GetRealpath(const std::string& __VSNC_IN path, std::string& __VSNC_OUT rpath) noexcept
{
	char curPath[254];
	GetCurrentDirectoryA(254, curPath);
	rpath = curPath + path;
	return true;
}

std::string vsnc::utils::VFile::GetDirname(const std::string& __VSNC_IN filename) noexcept
{
	if (filename.empty()) return ".";
	auto pos = filename.rfind("\\");
	if (pos == 0)
	{
		return "\\";
	}
	else if (pos == std::string::npos)
	{
		auto pos = filename.rfind("/");
		if (pos > 0) return filename.substr(0, pos);
		return ".";
	}
	return filename.substr(0, pos);
}



std::string vsnc::utils::VFile::GetBasename(const std::string& __VSNC_OUT filename) noexcept
{
	if (filename.empty()) return filename;
	auto pos = filename.rfind("\\");
	if (pos == std::string::npos)
	{
		auto pos = filename.rfind("/");
		if (pos > 0) return filename.substr(pos + 1);
		return filename;
	}
	return filename.substr(pos + 1);
}

bool vsnc::utils::VFile::OpenForRead(std::ifstream& __VSNC_IN_OUT ifs, const std::string& __VSNC_IN filename, const std::ios_base::openmode __VSNC_IN mode) noexcept
{
	ifs.open(filename.c_str(), mode);
	return ifs.is_open();
}

bool vsnc::utils::VFile::OpenForWrite(std::ofstream& __VSNC_IN_OUT ofs, const std::string& __VSNC_IN filename, const std::ios_base::openmode __VSNC_IN mode) noexcept
{
	ofs.open(filename.c_str(), mode);
	if (!ofs.is_open())
	{
		// 如果是不存在的文件夹，也创建相关路径
		size_t length = filename.find_last_of("\\");
		if (length != std::string::npos)
		{
			std::string __path = filename.substr(0, length);
			__create_multiple_folders(__path);
		}
		ofs.open(filename.c_str(), mode);
	}
	return ofs.is_open();
}

bool vsnc::utils::VFile::WriteString(const std::string& __VSNC_IN filename, const std::string& __VSNC_IN context, const std::ios_base::openmode __VSNC_IN mode) noexcept
{
	std::ofstream ofs;
	ofs.open(filename.c_str(), std::ios_base::app);
	if (!ofs.is_open())
	{
		// 如果是不存在的文件夹，也创建相关路径
		size_t length = filename.find_last_of("\\");
		if (length != std::string::npos)
		{
			std::string __path = filename.substr(0, length);
			__create_multiple_folders(__path);
		}
		ofs.open(filename.c_str(), mode);
	}
	if (ofs.is_open())
	{
		ofs << context;
		ofs.close();
		return true;
	}
	return false;
}

bool vsnc::utils::VFile::WriteString(const char* __VSNC_IN filename, const std::string& __VSNC_IN context, const std::ios_base::openmode __VSNC_IN mode) noexcept
{
	std::string strFileName = filename;
	return WriteString(strFileName, context, mode);
}

bool vsnc::utils::VFile::WriteStream(const std::string& __VSNC_IN filename, uint8_t* __VSNC_IN data, const size_t __VSNC_IN length, const std::ios_base::openmode __VSNC_IN mode) noexcept
{
	std::ofstream ofs;
	ofs.open(filename.c_str(), std::ios_base::app);
	if (!ofs.is_open())
	{
		// 如果是不存在的文件夹，也创建相关路径
		size_t length = filename.find_last_of("\\");
		if (length != std::string::npos)
		{
			std::string __path = filename.substr(0, length);
			__create_multiple_folders(__path);
		}
		ofs.open(filename.c_str(), mode);
	}
	if (ofs.is_open())
	{
		ofs.write(reinterpret_cast<char*>(data), length);
		ofs.close();
		return true;
	}
	return false;
}

bool vsnc::utils::VFile::WriteStream(const char* __VSNC_IN filename, uint8_t* __VSNC_IN data, const size_t __VSNC_IN length, const std::ios_base::openmode __VSNC_IN mode) noexcept
{
	std::string strFileName = filename;
	return WriteStream(strFileName, data, length, mode);
}

