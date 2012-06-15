#include "net_trans.hpp"

void NET_TRANS :: sendData(float x, float y, float z, float rotateX, float rotateY, float rotateZ, bool shot, int hp){
	char buf[256];
	int flag;
	if(shot)
		flag = 1;
	else
		flag = 0;
	sprintf_s(buf, "x:%f,y:%f,z:%f,rotateX:%f,rotateY:%f,rotateZ:%f,shot:%d,hp:%d\0", x, y, z, rotateX, rotateY, rotateZ, flag, hp);
	send(buf);
}

bool NET_TRANS :: recvData(float* x, float* y, float* z, float* rotateX, float* rotateY, float* rotateZ, bool* shot, int* hp){
	int ishot=0;

	char str[256];
	if(recv(str) == 0)
		return false;

	sscanf_s(str, "x:%f,y:%f,z:%f,rotateX:%f,rotateY:%f,rotateZ:%f,shot:%d,hp:%d\0", x, y, z, rotateX, rotateY, rotateZ, &ishot, hp);

	if(ishot == 1)
		*shot = true;
	else
		*shot = false;

	return true;
}