#include "DxLib.h"

class BUILDING{
private:
	int ModelHandle;
public:
	BUILDING(VECTOR pos);
	~BUILDING();
	void display();
	bool collision(VECTOR pos, VECTOR rotate);
};

BUILDING :: BUILDING(VECTOR pos){
	ModelHandle = MV1LoadModel("model\\building\\building.mqo");
	MV1SetScale(ModelHandle, VGet(5.0f, 4.0f, 5.0f));
	MV1SetPosition(ModelHandle, pos);
	MV1SetupCollInfo(ModelHandle, -1, 5, 5, 5);
}

BUILDING :: ~BUILDING(){
	MV1DeleteModel(ModelHandle);
	MV1TerminateCollInfo(ModelHandle, -1) ;
}

void BUILDING :: display(){
	MV1DrawModel(ModelHandle);
}

bool BUILDING :: collision(VECTOR pos, VECTOR rotate){
	VECTOR pos1 = VGet(pos.x+600*sinf(rotate.y), pos.y+100.0f+200.0f-500*sinf(rotate.x), pos.z+600*cosf(rotate.y));
	VECTOR pos2 = VGet(pos.x-200*sinf(rotate.y), pos.y+100.0f+200.0f+500*sinf(rotate.x), pos.z-200*cosf(rotate.y));

	MV1_COLL_RESULT_POLY_DIM  result = MV1CollCheck_Capsule(ModelHandle, -1, pos1, pos2, 200.0f);
	if(result.HitNum > 0){
		MV1CollResultPolyDimTerminate(result);
		return true;
	}
	MV1CollResultPolyDimTerminate(result);
	return false;
}