#include "enemy_net.hpp"

ENEMY_NET :: ENEMY_NET(VECTOR pos, float rotate, SHOT* mS, NET_TRANS* net) : ENEMY(pos, rotate, mS){
	this->net = net;
	InitializeCriticalSection(&cs);
}

ENEMY_NET :: ~ENEMY_NET(){
	DeleteCriticalSection(&cs);
}
void ENEMY_NET :: start(ENEMY_NET* en){
	sflag1 = true;
	hTh = (HANDLE)_beginthreadex(NULL, 0, &thread, en, 0, &thID);
	ResumeThread(hTh);
}
void ENEMY_NET :: stop(){
	sflag1 = false;
	WaitForSingleObject(this->hTh, INFINITE);
	CloseHandle(hTh);
}
