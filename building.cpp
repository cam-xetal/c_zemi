#include "building.hpp"


BUILDING :: BUILDING(){
	ModelHandle = MV1LoadModel("model\\building\\building.mqo");
	MV1SetScale(ModelHandle, VGet(5.0f, 4.0f, 5.0f));
	MV1SetPosition(ModelHandle, VGet(0, 0, 0));
	MV1SetupCollInfo(ModelHandle, -1, 5, 5, 5);
}

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

int BUILDING :: getModelHandle(){
	return ModelHandle;
}

void BUILDING :: display(){
	MV1DrawModel(ModelHandle);
}
