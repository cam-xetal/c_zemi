#include "net_udp.hpp"

NET_UDP ::NET_UDP(){
	if(WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
		exit(1);
	if((sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET){
		exit(1);
	}
}

NET_UDP :: NET_UDP(char* src_ip, int src_port, char* sin_ip, int sin_port){
	if(WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
		exit(1);
	if((sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET){
		exit(1);
	}
	setSrcAddr(src_ip, src_port);
	setSinAddr(sin_ip, sin_port);
}

NET_UDP :: ~NET_UDP(){
	shutdown(sock, SD_BOTH);
	closesocket(sock);
	WSACleanup();
}

void NET_UDP :: setSrcAddr(char* ip, int port){
	src_addr.sin_family = AF_INET;
	src_addr.sin_port = htons(port);
	if(inet_addr(ip) == -1)
		exit(1);
	src_addr.sin_addr.S_un.S_addr = inet_addr(ip);
}

void NET_UDP :: setSinAddr(char* ip, int port){
	sin_addr.sin_family = AF_INET;
	sin_addr.sin_port = htons(port);
	if(inet_addr(ip) == -1)
		exit(1);
	sin_addr.sin_addr.S_un.S_addr = inet_addr(ip);
}

void NET_UDP :: setBind(){
	 bind(sock, (struct sockaddr *)&src_addr, sizeof(src_addr));
}

void NET_UDP :: send(char* str){
	sendto(sock, str, strlen(str), 0, (struct sockaddr *)&sin_addr, sizeof(sin_addr));
}

int NET_UDP :: recv(char* str){
	int sin_size;
	struct sockaddr_in clt;
	sin_size = sizeof(struct sockaddr_in);
	int i = recvfrom(sock, str, sizeof(char)*256, 0,  (struct sockaddr *)&clt, &sin_size);

	return i;
}