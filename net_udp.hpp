#include <WinSock2.h>
#include <stdio.h>
#include <string.h>


class NET_UDP{
private:
	WSADATA wsaData;
	SOCKET sock;
	struct sockaddr_in sin_addr;
	struct sockaddr_in src_addr;
public:
	NET_UDP();
	NET_UDP(char* src_ip, int src_port, char* sin_ip, int sin_port);
	~NET_UDP();
	SOCKET getSock();
	void setSrcAddr(char* ip, int port);
	void setSinAddr(char* ip, int port);
	void setBind();
	void send(char* str);
	int recv(char* str);
};