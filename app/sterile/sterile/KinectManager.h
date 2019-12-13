#pragma once

#include <k4a/k4a.h>
#include <k4abt.h>
#include <opencv2/opencv.hpp>

class KinectManager
{
private:
	k4a_device_configuration_t _config;
	k4a_device_t _device;
	k4abt_tracker_t _tracker;
	k4a_transformation_t _transformation;
	void UpdateDepthImage(k4a_capture_t sensor_capture);

public:
	KinectManager();
	~KinectManager();

	void InitializeKinect();
	void InitializeBodyTracker();
	k4abt_frame_t GetBodyTrackingResult();
	void ShutDown();

	cv::Mat DepthImage;
};

