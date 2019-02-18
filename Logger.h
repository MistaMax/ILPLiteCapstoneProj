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
private:
	static ofstream& getLoggerFile();
	Logger();
	~Logger();
public:
	Logger(Logger const&) = delete;
	void operator=(Logger const&) = delete;
};

