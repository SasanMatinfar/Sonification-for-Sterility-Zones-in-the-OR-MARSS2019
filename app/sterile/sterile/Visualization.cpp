#include "Visualization.h"
#include <vector>;

namespace Visualization
{

	cv::Mat TintGreen(cv::Mat img)
	{
		return Tint(img, 0, 2);
	}

	cv::Mat TintRed(cv::Mat img)
	{
		return Tint(img, 0, 1);
	}

	cv::Mat Tint(cv::Mat img, int ch1, int ch2)
	{
		cv::Mat tintedImage;
		cv::cvtColor(img, tintedImage, CV_GRAY2BGR);
		cv::Mat channels[3];
		cv::split(tintedImage, channels);
		channels[ch1] = cv::Mat::zeros(tintedImage.rows, tintedImage.cols, CV_16U);
		channels[ch2] = cv::Mat::zeros(tintedImage.rows, tintedImage.cols, CV_16U);
		cv::merge(channels, 3, tintedImage);
		return tintedImage;
	}
}