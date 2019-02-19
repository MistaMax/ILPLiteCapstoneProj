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
	VectorXd b(nr), c(nc), A_eq(nr);

	data->A = A;
	data->b = b;
	data->c = c;
	data->A_eq = A_eq;

}
//reads in the data and outputs it through the parameter
void dataLoader::readFile(ILPData *data) 
{
	ifstream matrixFile;
	string input;
	matrixFile.open("input.txt");
	Logger::getInstance().logInfo("Opened the configuration text file");
	matrixFile >> input;
	int x = stoi(input);
	matrixFile >> input;
	int y = stoi(input);
	initDataMatricies(data, y, x);
	string cmd;
	while (matrixFile >> input) {
		cmd = input;
		if (cmd == "A:") {
			//printing out the matrix
			for (int i = 0; i < y; i++) {
				for (int j = 0; j < x; j++) {
					matrixFile >> input;
					data->A(j, i) = stoi(input);
				}
			}
			cout << cmd << endl << data->A << endl;
		}
		else if (cmd == "b:") {
			for (int i = 0; i < x; i++) {
				matrixFile >> input;
				data->b(i) = stoi(input);
			}
			cout << cmd << endl << data->b << endl;
		}
		else if (cmd == "c:") {
			for (int i = 0; i < y; i++) {
				matrixFile >> input;
				data->c(i) = stoi(input);
			}
			cout << cmd << endl << data->c << endl;
		}
		else if (cmd == "A_eq:") {
			for (int i = 0; i < x; i++) {
				matrixFile >> input;
				data->A_eq(i) = stoi(input);
			}
			cout << cmd << endl << data->A_eq << endl;
		}
		else {
			Logger::getInstance().logInfo("Error: command not found");
		}
	}
	matrixFile.close();
	Logger::getInstance().logInfo("Closed the configuration text file");
}

dataLoader::dataLoader()
{
	Logger::getInstance().logInfo("Initialized data loader");
}

dataLoader::~dataLoader()
{
	Logger::getInstance().logInfo("Deconstructing data loader");
}
