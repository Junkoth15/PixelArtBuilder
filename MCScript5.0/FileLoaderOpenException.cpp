#include "FileLoaderOpenException.h"

FileLoaderOpenException::FileLoaderOpenException(const string& message):
	runtime_error("FileLoaderOpenException:�ļ��򿪴���:" + message)
{
}

//const char* FileLoaderOpenException::what() const
//{
//	return string("FileLoaderOpenException:�ļ��򿪴���:"+message).c_str();
//}
