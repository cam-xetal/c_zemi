#include "DxLib.h"
#include "net_trans.h"
#include "enemy_net.h"

ENEMY_NET :: ENEMY_NET(VECTOR pos, float rotate, SHOT* mS, NET_TRANS* net) : ENEMY(pos, rotate, mS){
	this->net = net;
}

ENEMY_NET :: ~ENEMY_NET(){
	delete net;
}
void ENEMY_NET :: start(ENEMY_NET* en){
	hTh = (HANDLE)_beginthreadex(NULL, 0, &thread, en, 0, &thID);
	ResumeThread(hTh);
}
void ENEMY_NET :: stop(){
	TerminateThread(hTh, 0);
}