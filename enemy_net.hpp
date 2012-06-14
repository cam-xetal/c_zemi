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
	void start(ENEMY_NET* en);
	void stop();
	void enterCritical();
	void leaveCritical();
};

inline void ENEMY_NET :: control(){
	bool shot;
	EnterCriticalSection(&cs);
	net->recvData(&this->x, &this->y, &this->z, &this->rotateX, &this->rotateY, &this->rotateZ, &shot, &hp);
	if(shot){
		this->shot();
	}
	LeaveCriticalSection(&cs);
}
inline unsigned __stdcall ENEMY_NET :: thread(void* param){
	ENEMY_NET* en = (ENEMY_NET*)param;
	while(1)
		en->control();
	return 0;
}
inline int ENEMY_NET :: shot(){
	//�e�̔���
	mS->newShots(	VGet(x+125*cos(PI-rotateY), y+250.0f, z+125*sin(PI-rotateY)),
					VGet(x-125*cos(PI-rotateY), y+250.0f, z-125*sin(PI-rotateY)),
					VGet(0, rotateY-0.0025f, 0),
					VGet(0, rotateY+0.0025f, 0));
	return 0;
}

inline 	void ENEMY_NET :: enterCritical(){
	EnterCriticalSection(&cs);
}
inline 	void ENEMY_NET :: leaveCritical(){
	LeaveCriticalSection(&cs);
}