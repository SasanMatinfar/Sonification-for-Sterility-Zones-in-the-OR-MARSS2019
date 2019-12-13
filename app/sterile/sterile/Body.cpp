#include "Body.h"
#include <k4abt.h>
#include "Utilities.h"

Body::Body(k4abt_frame_t frame, size_t index)
{
	k4abt_frame_get_body_skeleton(frame, int(index), &Skeleton);
	ID = k4abt_frame_get_body_id(frame, index);
	HipPlane = Plane::Plane(Utilities::JointToCVPoint(GetLeftHip()), Utilities::VectorBetweenTwoJoints(GetPelvis(), GetNavel()));
	HeadPlane = Plane::Plane(Utilities::JointToCVPoint(GetLeftShoulder()), Utilities::VectorBetweenTwoJoints(GetNeck(), GetChest()));
	LeftHand = Hand(GetLeftWrist(), GetLeftElbow());
	RightHand = Hand(GetRightWrist(), GetRightElbow());
}

Body::Body()
{
}

Body::~Body()
{
}

k4abt_joint_t Body::GetNeck()
{
	return Skeleton.joints[K4ABT_JOINT_NECK];
}

k4abt_joint_t Body::GetLeftShoulder()
{
	return Skeleton.joints[K4ABT_JOINT_SHOULDER_LEFT];
}

k4abt_joint_t Body::GetChest()
{
	return Skeleton.joints[K4ABT_JOINT_SPINE_CHEST];
}

k4abt_joint_t Body::GetLeftWrist()
{
	return Skeleton.joints[K4ABT_JOINT_WRIST_LEFT];
}

k4abt_joint_t Body::GetRightWrist()
{
	return Skeleton.joints[K4ABT_JOINT_WRIST_RIGHT];
}

k4abt_joint_t Body::GetLeftHip()
{
	return Skeleton.joints[K4ABT_JOINT_HIP_LEFT];
}

k4abt_joint_t Body::GetRightHip()
{
	return Skeleton.joints[K4ABT_JOINT_HIP_RIGHT];
}

k4abt_joint_t Body::GetPelvis()
{
	return Skeleton.joints[K4ABT_JOINT_PELVIS];
}

k4abt_joint_t Body::GetLeftElbow()
{
	return Skeleton.joints[K4ABT_JOINT_ELBOW_LEFT];
}

k4abt_joint_t Body::GetRightElbow()
{
	return Skeleton.joints[K4ABT_JOINT_ELBOW_RIGHT];
}

k4abt_joint_t Body::GetNavel()
{
	return Skeleton.joints[K4ABT_JOINT_SPINE_NAVAL];
}