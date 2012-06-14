#ifndef NET_TRANS_B

#define NET_TRANS_B

#include <stdio.h>
#include "net_udp.hpp"
//#include "DxLib.h"

class NET_TRANS : public NET_UDP{
private:
public:
	NET_TRANS(char* src_ip, int src_port, char* sin_ip, int sin_port) : NET_UDP(src_ip, src_port, sin_ip, sin_port){}
	
	void sendData(float x, float y, float z, float rotateX, float rotateY, float rotateZ, bool shot, int hp){
		char buf[256];
		int flag;

		if(shot)
			flag = 1;
		else
			flag = 0;
		sprintf_s(buf, "x:%f,y:%f,z:%f,rotateX:%f,rotateY:%f,rotateZ:%f,shot:%d,hp:%d", x, y, z, rotateX, rotateY, rotateZ, flag, hp);
		send(buf);
	}

	bool recvData(float* x, float* y, float* z, float* rotateX, float* rotateY, float* rotateZ, bool* shot, int* hp){
		int ishot=0;
		
		char str[256];
		if(recv(str) == 0)
			return false;
				
		sscanf_s(str, "x:%f,y:%f,z:%f,rotateX:%f,rotateY:%f,rotateZ:%f,shot:%d,hp:%d", x, y, z, rotateX, rotateY, rotateZ, &ishot, hp);

		if(ishot == 1)
			*shot = true;
		else
			*shot = false;

		return true;
	}
};

#endif