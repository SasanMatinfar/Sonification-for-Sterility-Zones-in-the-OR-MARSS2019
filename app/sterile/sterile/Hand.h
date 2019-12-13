#pragma once
#include <k4abt.h>
#include <opencv2/opencv.hpp>

class Hand
{
public:
	Hand(k4abt_joint_t wrist, k4abt_joint_t elbow);
	Hand();
	~Hand();
	cv::Point3f Position;
};

