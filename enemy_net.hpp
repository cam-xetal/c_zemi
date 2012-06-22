#include <process.h>
#include "enemy.hpp"
#include "DxLib.h"
#include "net_trans.hpp"

class ENEMY_NET : public ENEMY{
private:
	CRITICAL_SECTION cs;
	NET_TRANS* net;
	unsigned int thID;
	HANDLE hTh;
	//inline--start
	void control();
	static unsigned __stdcall thread(void* param);
	int shot();
	//inline--end
public:
	ENEMY_NET(VECTOR pos, float rotate, SHOT* mS, NET_TRANS* net);
	~ENEMY_NET();
	NET_TRANS* getNet();
	void start(ENEMY_NET* en);
	void stop();
	void enterCritical();
	void leaveCritical();
};

inline void ENEMY_NET :: control(){
	bool shot;
	net->recvData(&this->x, &this->y, &this->z, &this->rotateX, &this->rotateY, &this->rotateZ, &shot, &hp);
	if(shot){
		EnterCriticalSection(&cs);
		this->shot();
		LeaveCriticalSection(&cs);
	}
}
inline unsigned __stdcall ENEMY_NET :: thread(void* param){
	fd_set fds, readfds;
	struct timeval tv;

	tv.tv_sec =  1;
	tv.tv_usec = 0;

	ENEMY_NET* en = (ENEMY_NET*)param;

	FD_ZERO(&readfds);
	FD_SET(en->getNet()->getSock(), &readfds);
	while(sflag1){	
		memcpy(&fds, &readfds, sizeof(fd_set));
		select(0, &fds, NULL, NULL, &tv);
		if(FD_ISSET(en->getNet()->getSock(), &fds)) {

			en->control();
		}
	}
	return 0;
}
inline int ENEMY_NET :: shot(){
	//’e‚Ì”­ŽË
	mS->newShots(	VGet(x+125*cos(PI-rotateY), y+250.0f, z+125*sin(PI-rotateY)),
					VGet(x-125*cos(PI-rotateY), y+250.0f, z-125*sin(PI-rotateY)),
					VGet(rotateX, rotateY-0.0025f, rotateZ),
					VGet(rotateX, rotateY+0.0025f, rotateZ));
	return 0;
}

inline NET_TRANS* ENEMY_NET :: getNet(){
	return this->net;
}

inline 	void ENEMY_NET :: enterCritical(){
	EnterCriticalSection(&cs);
}
inline 	void ENEMY_NET :: leaveCritical(){
	LeaveCriticalSection(&cs);
}