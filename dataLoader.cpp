#include "pch.h"
#include "dataLoader.h"
#include "Logger.h"
#include <fstream>



using namespace std;

//Initializes the matricies for the data with the number of rows and number of collumns
//not actual matricies used, this is just a proof of concept
//look at the matlab/utilities/misc/getData.m
void initDataMatricies(ILPData *data, int nr, int nc)
{
	MatrixXd A(nr, nc);
	VectorXd b(nr), c(nc), A_eq(nr), b_Eq(nc), lb(nr);

	data->A = A;
	data->b = b;
	data->c = c;
	data->A_eq = A_eq;
	data->c0 = 0;
	//set defaults for the rest of the values here
	//check getData.m for a basic idea
}
//reads in the data and outputs it through the parameter
void dataLoader::readFile(ILPData *data) 
{
	ifstream configFile;
	string input, cmd;

	configFile.open("config.txt");
	while (configFile >> input) {
		cmd = input;
		if (cmd == "display:") {
			configFile >> input;
			if (stoi(input) == 1)
				Logger::getInstance().setConsoleDisplayState(true);
			else
				Logger::getInstance().setConsoleDisplayState(false);
		}
		else if (cmd == "console:") {
			configFile >> input;
			if (stoi(input) == 1)
				Logger::getInstance().setLoggerWriteState(true);
			else
				Logger::getInstance().setLoggerWriteState(false);
		}
	}

	ifstream matrixFile;
	matrixFile.open("inputData.txt");
	Logger::getInstance().logInfo("Opened the data text file");
	matrixFile >> input;
	int x = stoi(input);
	matrixFile >> input;
	int y = stoi(input);
	initDataMatricies(data, y, x);
	string mat;
	while (matrixFile >> input) {
		cmd = input;
		mat = "";
		Logger::getInstance().logInfo(cmd);
		if (cmd == "A:") {
			//printing out the matrix
			for (int i = 0; i < y; i++) {
				for (int j = 0; j < x; j++) {
					matrixFile >> input;
					data->A(j, i) = stoi(input);
					mat += to_string(stoi(input)) + " ";
				}
				mat += "\n";
			}
		}
		else if (cmd == "b:") {
			for (int i = 0; i < x; i++) {
				matrixFile >> input;
				data->b(i) = stoi(input);
				mat += to_string(stoi(input)) + "\n";
			}
		}
		else if (cmd == "c:") {
			for (int i = 0; i < y; i++) {
				matrixFile >> input;
				data->c(i) = stoi(input);
				mat += to_string(stoi(input)) + "\n";
			}
		}
		else if (cmd == "A_eq:") {
			for (int i = 0; i < x; i++) {
				matrixFile >> input;
				data->A_eq(i) = stoi(input);
				mat += to_string(stoi(input)) + "\n";
			}
		}
		else {
			Logger::getInstance().logInfo("Error: command not found");
		}
		Logger::getInstance().logInfo(mat);
	}
	matrixFile.close();
	Logger::getInstance().logInfo("Closed the data text file");
}

dataLoader::dataLoader()
{
	Logger::getInstance().logInfo("Initialized data loader");
}

dataLoader::~dataLoader()
{
	Logger::getInstance().logInfo("Deconstructing data loader");
}
