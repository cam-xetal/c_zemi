#include <WinSock2.h>
#include <stdio.h>

class NET_UDP{
private:
	WSADATA wsaData;
	SOCKET sock;
	struct sockaddr_in addr;
public:
	NET_UDP();
	NET_UDP(char* ip, int port);
	~NET_UDP();
	void setAddr(char* ip, int port);
	void setBind();
	void send(char* str);
	int recv(char* str);
};