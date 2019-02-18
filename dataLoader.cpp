#include "pch.h"
#include "dataLoader.h"
#include "Logger.h"
#include <fstream>

using namespace std;

dataLoader::dataLoader()
{
	ifstream matrixFile;
	string input;
	matrixFile.open("input.txt");
	Logger::getInstance().logInfo("Opened the configuration text file");
	//put while loop and switch for commands in the config file
	//replace the line below when implemented
	matrixFile >> input;
	matrixFile.close();
	Logger::getInstance().logInfo("Closed the configuration text file");
}

dataLoader::~dataLoader()
{
	Logger::getInstance().logInfo("Deconstructing data loader");
}
