#include <process.h>
#include "enemy.hpp"
#include "read_init.hpp"
#include "net_trans.hpp"

class ENEMY_NET : public ENEMY{
private:
	CRITICAL_SECTION cs;
	int port;
	char ip[16];
	NET_TRANS* net;
	unsigned int thID;
	HANDLE hTh;
	//inline--start
	void control(){
		bool shot;
		net->recvData(&this->x, &this->y, &this->z, &this->rotateX, &this->rotateY, &this->rotateZ, &shot, &hp);
		if(shot){
			EnterCriticalSection(&cs);
			this->shot();
			LeaveCriticalSection(&cs);
		}
	}
	static unsigned __stdcall thread(void* param){
		ENEMY_NET* en = (ENEMY_NET*)param;
		while(1)
			en->control();
		return 0;
	}
	int shot(){
		//’e‚Ì”­ŽË
		mS->newShot(VGet(x+125*cos(PI-rotateY), y+250.0f, z+125*sin(PI-rotateY)), 15, rotateY-0.025f, 85.0f);
		mS->newShot(VGet(x-125*cos(PI-rotateY), y+250.0f, z-125*sin(PI-rotateY)), 15, rotateY+0.025f, 85.0f);
		return 0;
	}
	//inline--end
public:
	ENEMY_NET(VECTOR pos, float rotate, SHOT* mS, NET_TRANS* net);
	~ENEMY_NET();
	void start(ENEMY_NET* en);
	void stop();
	void enterCritical(){
		EnterCriticalSection(&cs);
	}
	void leaveCritical(){
		LeaveCriticalSection(&cs);
	}
};