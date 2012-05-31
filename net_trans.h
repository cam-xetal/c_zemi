#include <stdio.h>
#include "net_udp.h"

class NET_TRANS : public NET_UDP{
private:
public:
	NET_TRANS(char* ip, int port) : NET_UDP(ip, port){}
	
	void sendData(float x, float y, float z, float rotate, bool shot){
		char buf[256];
		int flag;

		if(shot)
			flag = 1;
		else
			flag = 0;
		sprintf_s(buf, "x:%lf,y:%lf,z:%lf,rotate:%lf,shot:%d", x, y, z, rotate, flag);
		send(buf);
	}

	void recvData(float* x, float* y, float* z, float* rotate, bool* shot){
		int ishot=0;
		*x = 0.0;
		*y = 0.0;
		*z = 0.0;
		*rotate = 0.0;
		
		char str[256];
		recv(str);
				
		int i = sscanf_s(str, "x:%f,y:%f,z:%f,rotate:%f,shot:%d", x, y, z, rotate, &ishot);

		if(ishot == 1)
			*shot = true;
		else
			*shot = false;
	}
};