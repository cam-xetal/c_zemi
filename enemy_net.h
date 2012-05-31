#include "enemy.h"
#include "read_init.h"
#include "net_trans.h"

class ENEMY_NET : public ENEMY{
private:
	int port;
	char ip[16];
	NET_TRANS* net;
public:
	ENEMY_NET(VECTOR pos, float rotate, SHOT* mS) : ENEMY(pos, rotate, mS){
		READ_INIT* read;
		read = new READ_INIT();
		read->read(ip, &port);
		delete read;
		net = new NET_TRANS(ip, port);
	}

	~ENEMY_NET(){
		delete net;
	}

	void control(){
		bool shot;
		net->recvData(&this->x, &this->y, &this->z, &this->rotateY, &shot);
		if(shot)
			this->shot();
	}
};