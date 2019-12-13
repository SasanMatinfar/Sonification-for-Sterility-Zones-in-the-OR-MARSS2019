#include <opencv2/opencv.hpp>

#ifndef ZONE_H
#define ZONE_H

class Zone {


public:
	Zone();
	virtual float get_distance(const cv::Point3f &point) = 0;
	virtual void transmit_data(const float &distance) = 0;
	~Zone();
};

#endif