#include "pch.h"
#include "Logger.h"


using namespace std;
bool Logger::write;
bool Logger::display;
ofstream Logger::loggerFile;

Logger& Logger::getInstance()
{
	static Logger instance;
	return instance;
}

void Logger::logInfo(string info) 
{
	if(write)
		loggerFile << info << endl;
	if (display)
		cout << info << endl;
}

void Logger::setLoggerWriteState(bool writeState) {
	write = writeState;
}

void Logger::setConsoleDisplayState(bool displayState) {
	display = displayState;
}

Logger::Logger() {
	loggerFile.open("log.txt");
	write = true;
	display = true;
}

Logger::~Logger() {
	loggerFile.close();
}
