#include "Logger.h"
using namespace std;

void Logger::log(string func_name, string message)
{
	cout << func_name << ":" << message << endl;
}

void Logger::log(string message)
{
	cout << message << endl;
}
