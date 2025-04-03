#include "Logger.h"
#include<Windows.h>
using namespace std;
LoggerLevel Logger::current_level=LoggerLevel::Debug;

void Logger::log(LoggerLevel level, string message, string func_name, int line)
{
	if (static_cast<int>(level) < static_cast<int>(current_level)) return;
	string str;
	if (line != -1) {
		str += "line:" + to_string(line) + " ";
	}
	str += func_name + ":" + message;
	log(level, str);
}

static enum Colors {
	BLACK = 0,
	BLUE = FOREGROUND_BLUE,
	GREEN = FOREGROUND_GREEN,
	CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE,
	RED = FOREGROUND_RED,
	MAGENTA = FOREGROUND_RED | FOREGROUND_BLUE,
	YELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
	WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	INTENSITY = FOREGROUND_INTENSITY
};

void Logger::log(LoggerLevel level, string message)
{
	if (static_cast<int>(level) < static_cast<int>(current_level)) return;

	Colors textColor;
	string str;
	switch (level)
	{
	case LoggerLevel::Trace:
	{
		str += "Trace ";
		textColor = GREEN;
	}break;
	case LoggerLevel::Info:
	{
		str += "Info ";
		textColor = BLUE;
	}break;
	case LoggerLevel::Debug:
	{
		str += "Debug ";
		textColor = MAGENTA;
	}break;
	case LoggerLevel::Warning:
	{
		str += "Warning ";
		textColor = YELLOW;
	}break;
	case LoggerLevel::Error:
	{
		str += "Error ";
		textColor = RED;
	}break;
	default:
		break;
	}
	// 获取并保存原颜色
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	WORD originalAttrs = csbi.wAttributes;

	// 设置新颜色（保留原背景色）
	WORD newAttrs = (originalAttrs >> 4 << 4) | textColor;
	SetConsoleTextAttribute(hConsole, newAttrs);
	cout << str;
	SetConsoleTextAttribute(hConsole, originalAttrs);
	cout <<message << endl;
}
