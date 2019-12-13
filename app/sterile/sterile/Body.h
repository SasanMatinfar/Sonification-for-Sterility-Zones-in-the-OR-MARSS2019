#pragma once
#include <k4abt.h>
#include "Zone/Plane.h"
#include "Zone/Sphere.h"
#include "opencv2/opencv.hpp"
#include "Hand.h"

class Body
{
public:
	k4abt_skeleton_t Skeleton;
	uint32_t ID;
	Plane HipPlane;
	Plane HeadPlane;
	Hand LeftHand;
	Hand RightHand;

	Body();
	Body(k4abt_frame_t frame, size_t index);
	~Body();

	k4abt_joint_t GetNeck();
	k4abt_joint_t GetLeftShoulder();
	k4abt_joint_t GetChest();
	k4abt_joint_t GetLeftWrist();
	k4abt_joint_t GetRightWrist();
	k4abt_joint_t GetLeftHip();
	k4abt_joint_t GetRightHip();
	k4abt_joint_t GetPelvis();
	k4abt_joint_t GetLeftElbow();
	k4abt_joint_t GetRightElbow();
	k4abt_joint_t GetNavel();
};

