
#include "BodyManager.h"
#include "Utilities.h"
#include <math.h>

const double eps = 0.00001;

BodyManager::BodyManager()
{
	NumOfBodies = 0;
}


BodyManager::~BodyManager()
{
}

void BodyManager::InitFromFrame(k4abt_frame_t frame)
{
	delete [] Bodies;
	size_t num_bodies = k4abt_frame_get_num_bodies(frame);
	NumOfBodies = num_bodies;
	Bodies = new Body [num_bodies];
	for (size_t i = 0; i < num_bodies; i++)
	{
		Bodies[i] = Body(frame, i);
	}
}

std::map<uint32_t, std::vector<float> > BodyManager::GetDistances()
{
	std::map<uint32_t, std::vector<float> > distanceMap;
	for (int i = 0; i < NumOfBodies; i++)
	{
		std::vector<float> distances;
		distances.push_back(Bodies[i].HipPlane.get_distance(Bodies[i].LeftHand.Position));
		distances.push_back(Bodies[i].HipPlane.get_distance(Bodies[i].RightHand.Position));
		distances.push_back(Bodies[i].HeadPlane.get_distance(Bodies[i].LeftHand.Position));
		distances.push_back(Bodies[i].HeadPlane.get_distance(Bodies[i].RightHand.Position));
		distances.push_back(Utilities::Distance(Bodies[i].GetPelvis().position, Bodies[i].GetNeck().position));
		distanceMap.insert(std::pair<uint32_t, std::vector<float> >(Bodies[i].ID, distances));
	}
	return distanceMap;
}