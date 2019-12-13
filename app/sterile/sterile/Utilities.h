#pragma once
#include <k4abt.h>
#include <opencv2/opencv.hpp>

namespace Utilities
{
	cv::Point3f JointToCVPoint(k4abt_joint_t joint);
	k4abt_joint_t AvarageTwoJoints(k4abt_joint_t a, k4abt_joint_t b);
	float Distance(k4a_float3_t a, k4a_float3_t b);
	cv::Vec3f VectorBetweenTwoJoints(k4abt_joint_t start, k4abt_joint_t end);
}