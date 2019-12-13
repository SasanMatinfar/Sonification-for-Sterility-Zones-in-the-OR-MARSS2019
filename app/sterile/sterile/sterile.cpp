#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "KinectManager.h"
#include "BodyManager.h"
#include <k4abt.h>
#include <map>
#include <stdlib.h>
#include <map>
#include <vector>

#include "Zone/Plane.h"
#include "Zone/Sphere.h"

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

#include "Messenger.h"
#include <windows.h>

#include "TestDataReader.h"
#include "Sonification.h"
#include "Visualization.h"

#define PORT_A 57120
#define PORT_N 7444
#define WATER false

const std::string ADDRESS = "10.5.1.224";

std::map<int, int> ports = std::map<int, int> {
std::pair<int, int> (1, PORT_A), 
std::pair<int, int>(2, PORT_A),
std::pair<int, int>(3, PORT_A),
std::pair<int, int>(4, PORT_N)};

void getAndSetParameters(std::string &, int &, bool &, int &);

int main(int argc, char*argv[])
{
	std::string address;
	int port;
	bool water;
	int track;

	getAndSetParameters(address, port, water, track);

	Messenger * m = new Messenger(address.c_str(), port);
	
	//TestDataReader t = TestDataReader();
	//t.runTest(m);

	Sonification::Sonifier sonifier = Sonification::Sonifier(m, water, track);

	KinectManager kinectManager = KinectManager();
	kinectManager.InitializeKinect();
	kinectManager.InitializeBodyTracker();
	BodyManager bodyManager = BodyManager();

	cv::Mat depthImageColor;
	int frame_count = 0;
	do
	{
		frame_count++;
		k4abt_frame_t body_frame = kinectManager.GetBodyTrackingResult();
		if (body_frame != NULL)
		{
			bodyManager.InitFromFrame(body_frame);
			std::map<uint32_t, std::vector<float> > map = bodyManager.GetDistances();
			cv::namedWindow("DepthImage");
			if (sonifier.Sonify(map))
			{
				cv::imshow("DepthImage", Visualization::TintRed(kinectManager.DepthImage));
				
			}
			else
			{
				cv::imshow("DepthImage", Visualization::TintGreen(kinectManager.DepthImage));
			}
			cv::waitKey(1);
			/*
			for (int i=0; i < bodyManager.NumOfBodies; i++)
			{
				std::cout << "Body: " << bodyManager.Bodies[i].ID << "\t - distances Hip [l,r]: "
					<< map[bodyManager.Bodies[i].ID][0] << ", " << map[bodyManager.Bodies[i].ID][1] << std::endl;
				std::cout << "\t - distances Head [l,r]: " << map[bodyManager.Bodies[i].ID][2]
					<< ", " << map[bodyManager.Bodies[i].ID][3] << std::endl;
			}*/
		}
		k4abt_frame_release(body_frame);
	} while (true);

	m->Transmit(STOP, 0, 0);
	kinectManager.ShutDown();

	return 0;
}

void getAndSetParameters(std::string &address, int &port, bool &water, int &track)
{
	int music_int;

	std::cout << "Enter Server Address:" << std::endl;
	std::getline(std::cin, address);

	if (address.length() == 0)
	{
		address = ADDRESS;
	}

	//std::cout << "Enter Server Port:" << std::endl;
	//std::cin >> port;

	std::cout << "Choose the music:" << std::endl;
	std::cout << '\t';
	std::cout << "[1] The Autumn Leaves - Chet Baker(1974)" << std::endl;
	std::cout << '\t';
	std::cout << "[2] English Man in New York - Sting(1987)" << std::endl;
	std::cout << '\t';
	std::cout << "[3] Sousa, The Liberty Bell. Monty Python Theme Song - John P. Sousa" << std::endl;
	std::cout << '\t';
	std::cout << "[4] Dynamic Bamboo Sound - Navid Navab(2019)" << std::endl;

	std::cin >> music_int;

	water = music_int < 4 ? true : false;
	port = ports[music_int];
	track = music_int;
}