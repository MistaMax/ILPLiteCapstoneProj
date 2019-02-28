#pragma once
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class Logger
{
public:
	static Logger& getInstance();
	static void logInfo(string info);
	static void setLoggerWriteState(bool writeState);
	static void setConsoleDisplayState(bool displayState);
private:
	static ofstream loggerFile;
	static bool write;
	static bool display;
	Logger();
	~Logger();
public:
	Logger(Logger const&) = delete;
	void operator=(Logger const&) = delete;
};

