#include "Zone.h"

#ifndef SPHERE_H
#define SPHERE_H
namespace Sphere
{

	class Sphere : public Zone
	{

	public:
		~Sphere();
		Sphere();
		Sphere(const cv::Point3f &p, const float &r);
		float get_distance(const cv::Point3f &point);
		void transmit_data(const float & distance);
		void update_center(const cv::Point3f &p);

	private:
		cv::Point3f center;
		float radius;
	};
}
#endif

