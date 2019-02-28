#pragma once

#include "../ILPData.h"

#include <exception>
#include <string>
#include <iostream>

using namespace std;
struct PresolveException : public exception {
	string error;
	string getError() throw () {
		return error;
	}
	void setError(string er) {
		error = er;
	}
};

int presolve(ILPData *data);

void mk();