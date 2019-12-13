#pragma once
#include "Messenger.h"
#include <vector>
#include <map>

#define ENTER_NEGATIVE_PLANE "/root/enter_negative_plane"
#define ENTER_POSITIVE_PLANE "/root/enter_positive_plane"
#define ENTER_NEGATIVE_SPHERE "/root/enter_negative_sphere"
#define ENTER_POSITIVE_SPHERE "/root/enter_positive_sphere"
#define UPDATE_SPHERE "/root/update_sphere"
#define UPDATE_PLANE "/root/update_plane"
#define START "/root/start"
#define STOP "/root/stop"

#define N_START "/init/"
#define N_COMMAND "/sterile"

#define LEFT_HAND_PLANE 0
#define RIGHT_HAND_PLANE 1
#define LEFT_HAND_SPHERE 2
#define RIGHT_HAND_SPHERE 3
#define BODY_NORMAL_SIZE 4

namespace Sonification
{
	class Sonifier
	{
	public:
		Sonifier(Messenger * me, bool type, int track) : m(me), type(type), track(track) {};
		bool Sonify(std::map < uint32_t, std::vector<float>>);

	private:
		Messenger * m;
		float GetMinDistance(float, float);
		bool IsZoneChanged(float, float, float, float);
		int index_finder(std::vector<uint32_t> t, int key);
		bool isRunning = false;

		std::map < uint32_t, std::vector<float>> previous_values;
		std::vector<uint32_t> body_ids;
		bool type;
		int track;
	};
}

