#include "FileLoaderException.h"

FileLoaderOpenException::FileLoaderOpenException(const string& message):
	runtime_error(message),message(message)
{
}

const char* FileLoaderOpenException::what() const
{
	return string("FileLoaderOpenException:�ļ��򿪴���:"+message).c_str();
}
