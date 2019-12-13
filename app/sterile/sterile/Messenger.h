#pragma once

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

#include<string>

#define OUTPUT_BUFFER_SIZE 1024;


class Messenger
{
private:
	const char *address;
	int port;
	UdpTransmitSocket * transmitSocket;

public:
	Messenger(const char * address, int port);
	~Messenger();

	void Transmit(const char *, float body_id, float data);
};

