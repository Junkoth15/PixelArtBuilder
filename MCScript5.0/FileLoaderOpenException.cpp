#include "FileLoaderOpenException.h"

FileLoaderOpenException::FileLoaderOpenException(const string& message):
	runtime_error("FileLoaderOpenException:文件打开错误:" + message)
{
}

//const char* FileLoaderOpenException::what() const
//{
//	return string("FileLoaderOpenException:文件打开错误:"+message).c_str();
//}
