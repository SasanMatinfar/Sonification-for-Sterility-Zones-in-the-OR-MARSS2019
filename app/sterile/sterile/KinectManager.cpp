#include "pch.h"
#include "KinectManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <k4a/k4a.h>
#include <k4abt.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define VERIFY(result, error)                                                                            \
    if(result != K4A_RESULT_SUCCEEDED)                                                                   \
    {                                                                                                    \
        printf("%s \n - (File: %s, Function: %s, Line: %d)\n", error, __FILE__, __FUNCTION__, __LINE__); \
        exit(1);                                                                                         \
    }    

KinectManager::KinectManager()
{
}


KinectManager::~KinectManager()
{
}

void KinectManager::InitializeKinect()
{
	_config = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
	_config.depth_mode = K4A_DEPTH_MODE_NFOV_UNBINNED;

	VERIFY(k4a_device_open(0, &_device), "Open K4A Device failed!");
	VERIFY(k4a_device_start_cameras(_device, &_config), "Start K4A cameras failed!");
}

void KinectManager::InitializeBodyTracker()
{
	k4a_calibration_t sensor_calibration;
	VERIFY(k4a_device_get_calibration(_device, _config.depth_mode, _config.color_resolution, &sensor_calibration),
		"Get depth camera calibration failed!");

	_tracker = NULL;
	VERIFY(k4abt_tracker_create(&sensor_calibration, &_tracker), "Body tracker initialization failed!");

	_transformation = k4a_transformation_create(&sensor_calibration);
}

k4abt_frame_t KinectManager::GetBodyTrackingResult()
{
	k4abt_frame_t body_frame = NULL;
	k4a_capture_t sensor_capture;
	k4a_wait_result_t get_capture_result = k4a_device_get_capture(_device, &sensor_capture, K4A_WAIT_INFINITE);
	
	if (get_capture_result == K4A_WAIT_RESULT_SUCCEEDED)
	{
		k4a_wait_result_t queue_capture_result = k4abt_tracker_enqueue_capture(_tracker, sensor_capture, K4A_WAIT_INFINITE);
		k4a_capture_release(sensor_capture);
		if (queue_capture_result == K4A_WAIT_RESULT_TIMEOUT)
		{
			printf("Error! Add capture to tracker process queue timeout!\n");
		}
		else if (queue_capture_result == K4A_WAIT_RESULT_FAILED)
		{
			printf("Error! Add capture to tracker process queue failed!\n");
		}

		k4a_wait_result_t pop_frame_result = k4abt_tracker_pop_result(_tracker, &body_frame, K4A_WAIT_INFINITE);
		if (pop_frame_result == K4A_WAIT_RESULT_SUCCEEDED)
		{
			//size_t num_bodies = k4abt_frame_get_num_bodies(body_frame);
			//printf("%zu bodies are detected!\n", num_bodies);
		}
		else if (pop_frame_result == K4A_WAIT_RESULT_TIMEOUT)
		{
			printf("Error! Pop body frame result timeout!\n");
		}
		else
		{
			printf("Pop body frame result failed!\n");
		}
		UpdateDepthImage(sensor_capture);
	}
	else if (get_capture_result == K4A_WAIT_RESULT_TIMEOUT)
	{
		printf("Error! Get depth frame time out!\n");
	}
	else
	{
		printf("Get depth capture returned error: %d\n", get_capture_result);
	}

	return body_frame;
}

void KinectManager::UpdateDepthImage(k4a_capture_t sensor_capture)
{
	k4a_image_t color_image = k4a_capture_get_depth_image(sensor_capture); // get image metadata

	if (color_image != NULL)
	{
		// you can check the format with this function
																	  // get raw buffer
		uint8_t* buffer = k4a_image_get_buffer(color_image);

		// convert the raw buffer to cv::Mat
		int rows = k4a_image_get_height_pixels(color_image);
		int cols = k4a_image_get_width_pixels(color_image);
		DepthImage = cv::Mat(rows, cols, CV_16U, (void*)buffer, cv::Mat::AUTO_STEP);
		DepthImage *= 255;
		k4a_image_release(color_image);
	}
}

void KinectManager::ShutDown()
{
	k4abt_tracker_shutdown(_tracker);
	k4abt_tracker_destroy(_tracker);
	k4a_device_stop_cameras(_device);
	k4a_device_close(_device);
}