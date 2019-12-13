#include "TestDataReader.h"

std::vector<float> TestDataReader::getData()
{
	std::ifstream file("..\\..\\..\\data\\test_data.csv");

	std::vector<std::string> dataList;

	std::string line = "";
	// Iterate through each line and split the content using delimeter
	char delimeter = '\n';
	while (std::getline(file, line, delimeter)) {
		dataList.push_back(line);
	}
	// Close the File
	file.close();

	std::vector<float> result;
	for (std::string k : dataList)
	{
		result.push_back(atof(k.c_str()));
	}

	return result;
}

void TestDataReader::runTest(Messenger * m)
{
//	m->Transmit("/root/play", 0, 0);
	m->Transmit("/init", 0, 1);

	float old = 0;
	for (float k : this->getData())
	{
		Sleep(10);
		std::cout << k << std::endl;

		//if (k*old >= 0)
		//{
		//	m->Transmit("/root/change", k, 0);
		//}
		//else
		//{
		//	k < 0 ? m->Transmit("/root/negative", 0, 0) : m->Transmit("/root/positive", 0, 0);
		//	m->Transmit("/root/change", k, 0);
		//}

		//old = k;
		
		if (k < 0)
		{
			m->Transmit("/sterile", 0, 1);
		}
		else
		{
			m->Transmit("/sterile", 0, 1 - k);
		}
	}
}