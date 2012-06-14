#ifndef NET_TRANS_B

#define NET_TRANS_B

#include <stdio.h>
#include "net_udp.hpp"

class NET_TRANS : public NET_UDP{
private:
public:
	NET_TRANS(char* src_ip, int src_port, char* sin_ip, int sin_port) : NET_UDP(src_ip, src_port, sin_ip, sin_port){}
	void sendData(float x, float y, float z, float rotateX, float rotateY, float rotateZ, bool shot, int hp);
	bool recvData(float* x, float* y, float* z, float* rotateX, float* rotateY, float* rotateZ, bool* shot, int* hp);
};

#endif