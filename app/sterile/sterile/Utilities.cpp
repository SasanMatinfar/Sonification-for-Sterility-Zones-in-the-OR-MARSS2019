#include <math.h>
#include <k4abt.h>
#include <opencv2/opencv.hpp>

namespace Utilities
{
	cv::Point3f JointToCVPoint(k4abt_joint_t joint)
	{
		return cv::Point3f(joint.position.v[0], joint.position.v[1], joint.position.v[2]);
	}

	k4abt_joint_t AvarageTwoJoints(k4abt_joint_t a, k4abt_joint_t b)
	{
		k4abt_joint_t avg;
		for (int i = 0; i < 3; i++)
		{
			avg.position.v[i] = (a.position.v[i] + b.position.v[i]) / 2;
		}
		avg.orientation = a.orientation;
		return avg;
	}

	float Distance(k4a_float3_t a, k4a_float3_t b)
	{
		return sqrtf((a.v[0] - b.v[0])*(a.v[0] - b.v[0]) + (a.v[1] - b.v[1])*(a.v[1] - b.v[1]) + (a.v[2] - b.v[2])*(a.v[2] - b.v[2]));
	}

	cv::Vec3f VectorBetweenTwoJoints(k4abt_joint_t start, k4abt_joint_t end)
	{
		return cv::Vec3f(JointToCVPoint(end) - JointToCVPoint(start));
	}
}
