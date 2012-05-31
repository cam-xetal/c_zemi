#include <string.h>
#include "net_udp.h"

NET_UDP ::NET_UDP(){
	if(WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
		exit(1);
	if((sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET){
		exit(1);
	}
}

NET_UDP :: NET_UDP(char* ip, int port){
	if(WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
		exit(1);
	if((sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET){
		exit(1);
	}
	setAddr(ip, port);
}

NET_UDP :: ~NET_UDP(){
	shutdown(sock, SD_BOTH);
	closesocket(sock);
	WSACleanup();
}

void NET_UDP :: setAddr(char* ip, int port){
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	if(inet_addr(ip) == -1)
		exit(1);
	addr.sin_addr.S_un.S_addr = inet_addr(ip);//INADDR_ANY;
}

void NET_UDP :: setBind(){
	 bind(sock, (struct sockaddr *)&addr, sizeof(addr));
}

void NET_UDP :: send(char* str){
	sendto(sock, str, strlen(str), 0, (struct sockaddr *)&addr, sizeof(addr));
}

int NET_UDP :: recv(char* str){
	char buf[256];
	memset(buf, 0, sizeof(char)*256);
	int sin_size;
	struct sockaddr_in clt;
	sin_size = sizeof(struct sockaddr_in);
	sizeof(str);
	recvfrom(sock, str, sizeof(char)*256, 0,  (struct sockaddr *)&clt, &sin_size);
	//printf("%s\n", buf);
	//printf("%d\n", clt.sin_port);
	return 1;
}