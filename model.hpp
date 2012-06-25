#ifndef MODEL_B

#define MODEL_B

#include "Dxlib.h"
#include "shot.hpp"
#include <math.h>

class MODEL{
protected:
	int ModelHandle;
	int attachIndex;
	float animTime;
	float playTime;
	float x, y, z;
	float preX, preY, preZ;
	float ppX, ppY, ppZ;
	float x0, y0, z0;
	float rotateX, rotateY, rotateZ;
	float preRX, preRY, preRZ;
	float v;
	float r;
	SHOT* mS;
	int hp;
	int count;
	bool cflag;
	//inline--start
	void virtual init(void);
	void virtual displayHp(void);
	//inline--end
public:
	//inline--start
	MODEL(SHOT* mS, float rotateY);
	~MODEL();
	VECTOR getPos();
	VECTOR getVector();
	VECTOR getRotate();
	int getHp();
	int getModelHandle();
	int damageCheck(SHOT* oS);
	void doNotMove(bool flag);
	bool collision(VECTOR pos, VECTOR rotate);
	//inline--end
	void virtual display();
	void move(bool fFlag, bool bFlag, bool upFlag, bool rRFlag, bool lRFlag, bool vFlag);
	int virtual shot();
};

//private--start
inline void MODEL :: init(void){
	ModelHandle = 0;
	attachIndex = 0;
	animTime = 0;
	playTime = 0;
	hp = 100;
	x = y = z =0;
	preX = preY = preZ = 0;
	ppX = ppY = ppZ = 0;
	x0 = z0 = 0;
	y0 = 100.0;
	rotateX = rotateY = rotateZ = 0;
	v = 0;
	count = 0;
	cflag = false;
	r = 250.0f;
}

inline void MODEL :: displayHp(){
	DrawBox(400, 10, 600, 30, GetColor(125, 255, 0), FALSE);
	if(hp < 0)
		hp = 0;
	DrawBox(400, 10, 400+hp*2, 30, GetColor(125, 255, 0), TRUE);
}
//private--end

//public--start
inline MODEL :: MODEL(SHOT* mS, float rotateY){
	init();
	ModelHandle = MV1LoadModel("model\\heri\\heri.mv1");
	MV1SetFrameVisible(ModelHandle, 39, FALSE);
	MV1SetupCollInfo(ModelHandle, 39, 8, 16, 32);
	attachIndex = MV1AttachAnim(ModelHandle, 0, -1, FALSE);
	animTime = MV1GetAttachAnimTotalTime(ModelHandle, attachIndex);
	playTime = 0.0f;
	this->mS = mS;
	this->rotateY = rotateY;
}

inline MODEL :: ~MODEL(){
	MV1TerminateCollInfo(ModelHandle, 39);
	MV1DeleteModel(ModelHandle);
}

inline VECTOR MODEL :: getPos(){
	return VGet(this->x, this->y, this->z);
}

inline VECTOR MODEL :: getVector(){
	VECTOR tmp = VSub(VGet(x, y, z), VGet(preX, preY, preZ));
	if(tmp.x == 0 && tmp.z ==0)
		return VSub(VGet(x, y, z), VGet(ppX, ppY, ppZ));
	ppX = preX;
	ppY = preY;
	ppZ = preZ;
	return VSub(VGet(x, y, z), VGet(preX, preY, preZ));
}

inline VECTOR MODEL :: getRotate(){
	return VGet(rotateX, rotateY, rotateY);
}

inline int MODEL :: getHp(){
	return this->hp;
}

inline int MODEL :: getModelHandle(){
	return ModelHandle;
}

inline int MODEL :: damageCheck(SHOT* oS){
	if(hp > 0){
		int dcount = oS->collisionModel(ModelHandle);
		hp -= dcount*5;
	}else{
		hp = 0;
	}
	return hp;
}
inline void MODEL :: doNotMove(bool flag){
	if(!flag)
		return;
	this->x = this->preX;
	this->y = this->preY;
	this->z = this->preZ;
	this->rotateX = this->preRX;
	this->rotateY = this->preRY;
	this->rotateZ = this->preRZ;
}

inline bool MODEL :: collision(VECTOR pos, VECTOR rotate){
		MV1_COLL_RESULT_POLY_DIM  result;
		if(!cflag){
			r += 2.5f;
			if(r > 250.0f)
				r = 250.0f;
			VECTOR pos1 = VGet(pos.x+600*sinf(rotate.y), pos.y+100.0f+200.0f-500*sinf(rotate.x), pos.z+600*cosf(rotate.y));
			VECTOR pos2 = VGet(pos.x-200*sinf(rotate.y), pos.y+100.0f+200.0f+500*sinf(rotate.x), pos.z-200*cosf(rotate.y));
			result = MV1CollCheck_Capsule(ModelHandle, 39, pos1, pos2, r);
		}else{
			r -= 5.0f;
			if(r < 100.0f)
				r = 100.0f;
			VECTOR pos1 = VGet(pos.x+600*sinf(rotate.y), pos.y+100.0f+200.0f-500*sinf(rotate.x), pos.z+600*cosf(rotate.y));
			VECTOR pos2 = VGet(pos.x-200*sinf(rotate.y), pos.y+100.0f+200.0f+500*sinf(rotate.x), pos.z-200*cosf(rotate.y));
			result = MV1CollCheck_Capsule(ModelHandle, 39, pos1, pos2, r);
		}
		if(r == 100.0){
			cflag = true;
			return false;
		}
		if(result.HitNum > 0){
			MV1CollResultPolyDimTerminate(result);
			cflag = true;
			return true;
		}
		MV1CollResultPolyDimTerminate(result);
		cflag = false;
		return false;
	}
//public--end
#endif