#pragma once
#include <k4abt.h>
#include <vector>
#include <map>
#include "Body.h"

class BodyManager
{
public:
	Body* Bodies;
	int NumOfBodies;

	BodyManager();
	~BodyManager();

	void InitFromFrame(k4abt_frame_t frame);
	std::map<uint32_t, std::vector<float> > GetDistances();
};

