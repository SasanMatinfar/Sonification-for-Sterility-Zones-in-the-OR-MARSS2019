#pragma once
#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <windows.h>
#include <fstream>  

#include "Messenger.h"

class TestDataReader
{
public:
	std::vector<float> getData();
	void runTest(Messenger * m);
};