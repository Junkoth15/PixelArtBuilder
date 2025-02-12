#include "FileLoaderException.h"

FileLoaderOpenException::FileLoaderOpenException(const string& message):
	runtime_error(message),message(message)
{
}

const char* FileLoaderOpenException::what() const
{
	return string("FileLoaderOpenException:文件打开错误:"+message).c_str();
}
