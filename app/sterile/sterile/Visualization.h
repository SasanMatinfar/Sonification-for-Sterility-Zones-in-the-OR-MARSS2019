#pragma once
#include <opencv2/opencv.hpp>
#include "Zone/Plane.h"

namespace Visualization
{
	cv::Mat TintGreen(cv::Mat imge);
	cv::Mat TintRed(cv::Mat imge);
	cv::Mat Tint(cv::Mat img, int ch1, int ch2);
};

