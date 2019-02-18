#include "pch.h"
#include "Logger.h"

using namespace std;
Logger& Logger::getInstance()
{
	static Logger instance;
	return instance;
}

void Logger::logInfo(string info) 
{
	getLoggerFile() << info << endl;
}

ofstream& Logger::getLoggerFile() {
	static ofstream loggerFile;
	return loggerFile;
}

Logger::Logger() {
	getLoggerFile().open("log.txt");
}

Logger::~Logger() {
	getLoggerFile().close();
}
