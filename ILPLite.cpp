#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	ifstream matrixFile;
	string input;
	matrixFile.open("input.txt");
	matrixFile >> input;
	cout << input << endl;
	matrixFile.close();
	return 0;
}
