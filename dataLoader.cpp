#include "pch.h"
#include "dataLoader.h"
#include "Logger.h"
#include <fstream>



using namespace std;
//Initializes the matricies for the data with the number of rows and number of collumns
//not actual matricies used, this is just a proof of concept
void initDataMatricies(ILPData *data, int nr, int nc)
{
	MatrixXd A(nr, nc), b(nr, 1), c(nr, 1), A_eq(nr, 1);
	
	/*A = MatrixXd::Identity(nr, nc);
	b = MatrixXd::Identity(nr, 1);
	c = MatrixXd::Identity(nc, 1);
	A_eq = MatrixXd::Identity(nr, nc);*/

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
				//cout << "|";
				for (int j = 0; j < x; j++) {
					matrixFile >> input;
					data->A(j, i) = stoi(input);
					//cout << input << " ";
				}
				//cout << "|" << endl;
			}
			cout << cmd << endl << data->A << endl;
		}
		else if (cmd == "b:") {
			for (int i = 0; i < x; i++) {
				matrixFile >> input;
				data->b(i, 0) = stoi(input);
			}
			cout << cmd << endl << data->b << endl;
		}
		else if (cmd == "c:") {
			for (int i = 0; i < y; i++) {
				matrixFile >> input;
				data->c(i, 0) = stoi(input);
			}
			cout << cmd << endl << data->c << endl;
		}
		else if (cmd == "A_eq:") {
			for (int i = 0; i < x; i++) {
				matrixFile >> input;
				data->A_eq(i, 0) = stoi(input);
			}
			cout << cmd << endl << data->A_eq << endl;
		}
		else {
			Logger::getInstance().logInfo("Error: command not found");
		}
	}
	//cout << cmd << endl;
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
