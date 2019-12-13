#include "Sphere.h"


namespace Sphere
{
	Sphere::Sphere(const cv::Point3f &p1, const float &r) : center(p1), radius(r) {};

	Sphere::Sphere()
	{
	}

	Sphere::~Sphere()
	{
	}

	float Sphere::get_distance(const cv::Point3f &point)
	{
		float tmp = (float)sqrt(pow(point.x - center.x, 2.0) +
			pow(point.y - center.y, 2.0) +
			pow(point.z - center.z, 2.0));
		return (tmp - radius);
	}

	void Sphere::transmit_data(const float &distance)
	{
		//pass
	}

	void Sphere::update_center(const cv::Point3f &p)
	{
		this->center = p;
	}
}
