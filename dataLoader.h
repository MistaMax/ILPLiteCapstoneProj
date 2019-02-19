#pragma once
#include <string>
#include <iostream>
#include "ILPData.h"

class dataLoader
{
public:
	dataLoader();
	~dataLoader();
	void readFile(ILPData *data);
};
