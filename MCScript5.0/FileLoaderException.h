#pragma once
#include"NameSpace.h"
#include<stdexcept>
class FileLoaderOpenException:
	public std::runtime_error
{
private:
	string message;
public:
	FileLoaderOpenException(const string& message);
	virtual const char* what()const override;
};

