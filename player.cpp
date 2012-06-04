#include "player.h"

void PLAYER :: display(){
	displayXYZ();
	displayV();
	displayHp();
	SetCameraPositionAndTarget_UpVecY(VGet(cx, cy ,cz), VGet(x, y, z));
	MODEL :: display();
}
void PLAYER :: control(){
	bool fFlag = false;
	bool bFlag = false;
	bool upFlag = false;
	bool rRFlag = false;
	bool lRFlag = false;
	bool vFlag = false;

	//速度制御
	if(CheckHitKey(KEY_INPUT_UP)){
		vFlag = true;
	}
	//左右回転制御
	if(CheckHitKey(KEY_INPUT_D)){	//左回転
		lRFlag = true;
	}
	if(CheckHitKey(KEY_INPUT_A)){
		rRFlag = true;
	}
	//前後移動制御
	if(CheckHitKey(KEY_INPUT_W)){	//前移動
		fFlag = true;
	}
	if(CheckHitKey(KEY_INPUT_S)){	//後ろ移動
		bFlag =true;
	}
	//上昇
	if(CheckHitKey(KEY_INPUT_LSHIFT)){
		upFlag = true;
	}

	//移動
	move(fFlag, bFlag, upFlag, rRFlag, lRFlag, vFlag);
	//弾の発射
	sflag = false;
	if(CheckHitKey(KEY_INPUT_SPACE)){
		if(shot())
			sflag = true;
	}

	//カメラアングル
	cRotate = rotateY;

	//カメラ位置指定
	if(CheckHitKey(KEY_INPUT_DOWN)){
		return;
	}
	if(CheckHitKey(KEY_INPUT_RIGHT)){
		cRotate -= PI/4.0;
	}
	if(CheckHitKey(KEY_INPUT_LEFT)){			
		cRotate += PI/4.0;
	}
	if(cRotate > 2*PI)
		cRotate -= 2*PI;
	if(cRotate < 0)
		cRotate += 2*PI;

	cx = x + x0 + 1500*sinf(cRotate);
	cy = y + y0 + 300.0f;
	cz = z + z0 + 1500*cosf(cRotate);
}

void PLAYER :: send(){
	net->sendData(-this->x, this->y, -this->z, this->rotateX, this->rotateY+PI, this->rotateZ, sflag, hp);
}