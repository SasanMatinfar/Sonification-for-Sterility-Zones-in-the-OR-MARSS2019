#include "Plane.h"

Plane::Plane(const cv::Point3f &p, const cv::Vec3f &nr)
{
	cv::Vec3f normalized_normal = cv::normalize(nr);
	a = normalized_normal[0];
	b = normalized_normal[1];
	c = normalized_normal[2];

	cv::Point3f p_beta = p;
	p_beta.x = normalized_normal[0] * 5 + p.x;
	p_beta.y = normalized_normal[0] * 5 + p.y;
	p_beta.z = normalized_normal[0] * 5 + p.z;
	d = -p_beta.dot(normalized_normal);
}
Plane::Plane(const cv::Point3f &p1, const cv::Point3f &p2, const cv::Point3f &p3)
{
	cv::Vec3f v1 = p2 - p1;
	cv::Vec3f v2 = p3 - p1;
	cv::Vec3f normal = cv::normalize(v1.cross(v2));
	Plane(p1, normal);
}
Plane::Plane()
{
}
Plane::~Plane()
{
}
float Plane::get_distance(const cv::Point3f &point)
{
	return (this->a * point.x + this->b * point.y + this->c * point.z + this->d) /
		sqrt(a*a + b * b + c * c);
};
void Plane::transmit_data(const float &distance)
{
	//pass
}
void Plane::update_plane(const cv::Point3f &p1, const cv::Point3f &p2, const cv::Point3f &p3)
{
	//TO DO
	return;
}