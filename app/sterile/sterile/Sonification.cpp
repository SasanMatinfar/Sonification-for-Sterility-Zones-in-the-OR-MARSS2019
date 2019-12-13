#include "Sonification.h"
#include <iterator>
#include <vector>
#include <iostream>

using namespace Sonification;

bool Sonification::Sonifier::Sonify(std::map<uint32_t, std::vector<float>> all_data)
{
	bool isRed = false;

	for (std::pair<uint32_t, std::vector<float>> k : all_data)
	{
		if (index_finder(body_ids, k.first) == -1)
		{
			body_ids.push_back(k.first);
			int index = index_finder(body_ids, k.first);
			previous_values[index] = { 0, 0, 0, 0 };
			if (!isRunning)
			{
				type ? m->Transmit(START, index, track) : m->Transmit(N_START, index, track);
				isRunning = true;
			}
			
		}

		if (!type)
		{
			float hand_distance = GetMinDistance(
				GetMinDistance(k.second.at(LEFT_HAND_PLANE), k.second.at(RIGHT_HAND_PLANE)),
				GetMinDistance(k.second.at(LEFT_HAND_SPHERE), k.second.at(RIGHT_HAND_SPHERE)))
				/ k.second.at(BODY_NORMAL_SIZE);

			if (hand_distance < 0)
			{
				m->Transmit(N_COMMAND, 0, 1.0f);
				isRed = true;
			}
			else
			{
				m->Transmit(N_COMMAND, 0, 1.0f - (2.0f * hand_distance));
			}
			continue;
		}
		else
		{
			int index = index_finder(body_ids, k.first);
			std::vector<float> old_data = previous_values[index];

			bool hand_under_plane = (k.second.at(LEFT_HAND_PLANE) < 0.0f) || (k.second.at(RIGHT_HAND_PLANE) < 0.0f);
			bool hand_under_plane_old = (old_data.at(LEFT_HAND_PLANE) < 0.0f) || (old_data.at(RIGHT_HAND_PLANE) < 0.0f);

			bool hand_in_sphere = (k.second.at(LEFT_HAND_SPHERE) < 0.0f) || (k.second.at(RIGHT_HAND_SPHERE) < 0.0f);
			bool hand_in_sphere_old = (old_data.at(LEFT_HAND_SPHERE) < 0.0f) || (old_data.at(RIGHT_HAND_SPHERE) < 0.0f);

			bool planeZoneChanged = hand_under_plane != hand_under_plane_old;
			bool sphereZoneChanged = hand_in_sphere != hand_in_sphere_old;

			float min_hand_plane = GetMinDistance(k.second.at(LEFT_HAND_PLANE), k.second.at(RIGHT_HAND_PLANE));
			float min_hand_sphere = GetMinDistance(k.second.at(LEFT_HAND_SPHERE), k.second.at(RIGHT_HAND_SPHERE));

			if (planeZoneChanged && hand_under_plane)
			{
				m->Transmit(ENTER_NEGATIVE_PLANE, index, min_hand_plane);
			}
			if (planeZoneChanged && !hand_under_plane)
			{
				m->Transmit(ENTER_POSITIVE_PLANE, index, min_hand_plane);
			}
			if (sphereZoneChanged && hand_in_sphere)
			{
				m->Transmit(ENTER_NEGATIVE_SPHERE, index, min_hand_sphere);
			}
			if (sphereZoneChanged && !hand_in_sphere)
			{
				m->Transmit(ENTER_POSITIVE_SPHERE, index, min_hand_sphere);
			}

			//m->Transmit(UPDATE_PLANE, index, min_hand_plane);
			//m->Transmit(UPDATE_SPHERE, index, min_hand_plane);

			previous_values[index] = k.second;
			isRed = isRed || hand_in_sphere || hand_under_plane;
		}
	}

	return isRed;
}

float Sonification::Sonifier::GetMinDistance(float left, float right)
{
	return (left < right) ? left : right;
}

bool Sonification::Sonifier::IsZoneChanged(float l, float l_old, float r, float r_old)
{

	return GetMinDistance(l ,l_old) * GetMinDistance(r, r_old) < 0;
}

int Sonification::Sonifier::index_finder(std::vector<uint32_t> t, int key)
{
	int i = 0;
	for (int k : t)
	{
		if (k == key)
			return i;
		i++;
	}
	return -1;
}