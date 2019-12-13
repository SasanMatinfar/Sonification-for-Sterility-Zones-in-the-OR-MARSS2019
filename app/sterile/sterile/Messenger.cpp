#include "Messenger.h"
#include <iostream>

#define OUTPUT_BUFFER_SIZE 1024

Messenger::Messenger(const char * address, int port) : address(address), port(port) {
	transmitSocket = new UdpTransmitSocket(IpEndpointName(address, port));
};

Messenger::~Messenger()
{
}

void Messenger::Transmit(const char * dir, float body_id, float data)
{
	char buffer[OUTPUT_BUFFER_SIZE];
	osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE);

	p << osc::BeginBundleImmediate
		<< osc::BeginMessage(dir)
		<< data << body_id <<
		osc::EndMessage
		<< osc::EndBundle;

	this->transmitSocket->Send(p.Data(), p.Size());

	//std::cout << dir << std::endl;
}