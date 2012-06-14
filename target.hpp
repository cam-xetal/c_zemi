#include "DxLib.h"
#include <time.h>
#include "parameter.h"


class TARGET{
private:
	int ModelHandle;
	bool dflag;
	float x, y, z;
	float rotate;
	//inline--start
	void getRand();
	//inline--end
public:
	//inline--start
	TARGET(void);
	~TARGET();
	void newTarget();
	void delTarget();
	void display();
	int getModelHandle();
	bool collision(VECTOR pos, VECTOR rotate);
	//inline--end
};

//private--start
inline void TARGET :: getRand(){
	x = (float)(((MAX_X-500.0f)-(MIN_X+500.0f)+1.0f)*((double)rand()/(double)(RAND_MAX+0.1f))+(MIN_X+500.0f));
	y = (float)(((MAX_Y-150.0f)-MIN_Y+1.0f)*((double)rand()/(double)(RAND_MAX+0.1f))+MIN_Y+50);
	z = (float)(((MAX_Z-500.0f)-(MIN_Z+500.0f)+1.0f)*((double)rand()/(double)(RAND_MAX+0.1f))+(MIN_Z+500.0f));
	rotate = (float)((2*PI+1.0f)*((double)rand()/(double)(RAND_MAX+0.1f)));
}
//private--end

//public--start
inline TARGET :: TARGET(void){
	srand((unsigned)time(NULL));
	ModelHandle = MV1LoadModel("model\\target\\target.mqo");
	MV1SetScale(ModelHandle, VGet(3.0f, 3.0f, 3.0f));
}

inline TARGET :: ~TARGET(){
	MV1TerminateCollInfo(ModelHandle, -1);
	MV1DeleteModel(ModelHandle);
}

inline void TARGET :: newTarget(){
	dflag = true;
	getRand();
	MV1SetPosition(ModelHandle, VGet(x, y, z));
	MV1SetRotationXYZ(ModelHandle, VGet(0, rotate, 0));
	MV1SetupCollInfo(ModelHandle, -1, 8, 8, 8);
}

inline void TARGET :: delTarget(){
	dflag = false;
	MV1TerminateCollInfo(ModelHandle, -1);
}

inline void TARGET :: display(){
	if(dflag)
		MV1DrawModel(ModelHandle);
}

inline int TARGET :: getModelHandle(){
	return ModelHandle;
}

inline bool TARGET :: collision(VECTOR pos, VECTOR rotate){
	VECTOR pos1 = VGet(pos.x+600*sinf(rotate.y), pos.y+100.0f+200.0f-500*sinf(rotate.x), pos.z+600*cosf(rotate.y));
	VECTOR pos2 = VGet(pos.x-200*sinf(rotate.y), pos.y+100.0f+200.0f+500*sinf(rotate.x), pos.z-200*cosf(rotate.y));

	MV1_COLL_RESULT_POLY_DIM  result = MV1CollCheck_Capsule(ModelHandle, -1, pos1, pos2, 210.0f);
	if(result.HitNum > 0){
		MV1CollResultPolyDimTerminate(result);
		return true;
	}
	MV1CollResultPolyDimTerminate(result);
	return false;
}
//public--end