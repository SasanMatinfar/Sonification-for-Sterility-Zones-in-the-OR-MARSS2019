#pragma once
#include "Zone.h"

class Plane : public Zone
{

public:
	~Plane();
	Plane();
	Plane(const cv::Point3f &p1, const cv::Vec3f &nr);
	Plane(const cv::Point3f &p1, const cv::Point3f &p2, const cv::Point3f &p3);

	float get_distance(const cv::Point3f &point); // inline OK
	void transmit_data(const float & distance);
	void update_plane(const cv::Point3f &p1, const cv::Point3f &p2, const cv::Point3f &p3);

private:
	float a, b, c, d;
};
