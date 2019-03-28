#include "pch.h"
#include "dataLoader.h"
#include "Logger.h"
#include <fstream>
#include <vector>



using namespace std;

//Initializes the matricies for the data with the number of rows and number of collumns
//not actual matricies used, this is just a proof of concept
//look at the matlab/utilities/misc/getData.m
void initDataMatricies(ILPDenseData *data, int nr, int nc)
{
	MatrixXd A(nr, nc);
	VectorXd b(nr), c(nc), Eq(nr), b_Eq(nc), lb(nr);

	data->A = A;
	data->b = b;
	data->c = c;
	data->Eq = Eq;
	data->c0 = 0;
	//set defaults for the rest of the values here
	//check getData.m for a basic idea
}

void convertToSparse(ILPDenseData *denseData, ILPData *sparseData) {
	Logger::getInstance().logInfo("Starting conversion from Dense to Sparse");
	sparseData->A = denseData->A.sparseView();
	sparseData->b = denseData->b.sparseView();
	sparseData->c = denseData->c.sparseView();
	sparseData->Eq = denseData->Eq.sparseView();
	sparseData->c0 = denseData->c0;
	Logger::getInstance().logInfo("Ending conversion from Dense to Sparse");
}
//reads in the data and outputs it through the parameter

void dataLoader::readFile(ILPData *sparseData) 
{
	ILPDenseData data;

	ifstream configFile;
	string input, cmd;

	configFile.open("config.txt");
	while (configFile >> input) {
		cmd = input;
		if (cmd == "display:") {
			configFile >> input;
			if (stod(input) == 1)
				Logger::getInstance().setConsoleDisplayState(true);
			else
				Logger::getInstance().setConsoleDisplayState(false);
		}
		else if (cmd == "console:") {
			configFile >> input;
			if (stod(input) == 1)
				Logger::getInstance().setLoggerWriteState(true);
			else
				Logger::getInstance().setLoggerWriteState(false);
		}
	}

	ifstream matrixFile;
	matrixFile.open("inputData.txt");
	Logger::getInstance().logInfo("Opened the data text file");
	matrixFile >> input;
	int x = stod(input);
	matrixFile >> input;
	int y = stod(input);
	initDataMatricies(&data, y, x);
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
					data.A(i, j) = stod(input);
					mat += to_string(stod(input)) + " ";
				}
				mat += "\n";
			}
		}
		else if (cmd == "b:") {
			for (int i = 0; i < x; i++) {
				matrixFile >> input;
				data.b(i) = stod(input);
				mat += to_string(stod(input)) + "\n";
			}
		}
		else if (cmd == "c:") {
			for (int i = 0; i < y; i++) {
				matrixFile >> input;
				data.c(i) = stod(input);
				mat += to_string(stod(input)) + "\n";
			}
		}
		else if (cmd == "Eq:") {
			for (int i = 0; i < x; i++) {
				matrixFile >> input;
				data.Eq(i) = stod(input);
				mat += to_string(stod(input)) + "\n";
			}
		}
		else {
			Logger::getInstance().logInfo("Error: command not found");
		}
		Logger::getInstance().logInfo(mat);
	}
	matrixFile.close();
	Logger::getInstance().logInfo("Closed the data text file");
	convertToSparse(&data, sparseData);
}

dataLoader::dataLoader()
{
	Logger::getInstance().logInfo("Initialized data loader");
}

dataLoader::~dataLoader()
{
	Logger::getInstance().logInfo("Deconstructing data loader");
}
