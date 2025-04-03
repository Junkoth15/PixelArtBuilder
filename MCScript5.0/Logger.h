#pragma once
#include"NameSpace.h"
enum class LoggerLevel
{
	Trace,
	Debug,
	Info,
	Warning,
	Error
};

class Logger
{
public:
	static LoggerLevel current_level;
public:
	static void log(LoggerLevel level, string message,string func_name, int line = -1);
	static void log(LoggerLevel level, string message);
private:

};

#define LogTrace(message)	Logger::log(LoggerLevel::Trace,message,	__FUNCTION__,__LINE__)
#define LogInfo(message)	Logger::log(LoggerLevel::Info,message,	__FUNCTION__,__LINE__)
#define LogDebug(message)	Logger::log(LoggerLevel::Debug,message,	__FUNCTION__,__LINE__)
#define LogWarning(message) Logger::log(LoggerLevel::Warning,message,__FUNCTION__,__LINE__)
#define LogError(message)	Logger::log(LoggerLevel::Error,message,	__FUNCTION__,__LINE__)


