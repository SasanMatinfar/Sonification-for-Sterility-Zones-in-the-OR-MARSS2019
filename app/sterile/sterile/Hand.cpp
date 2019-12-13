#include "Hand.h"
#include "Utilities.h"


Hand::Hand(k4abt_joint_t wrist, k4abt_joint_t elbow)
{
	cv::Point3f wristPoint = Utilities::JointToCVPoint(wrist);
	Position = wristPoint + (wristPoint - Utilities::JointToCVPoint(elbow)) / 2;
}

Hand::Hand()
{
}

Hand::~Hand()
{
}
