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
	TARGET(void);
	~TARGET();
	void newTarget();
	void delTarget();
	void display();
	int getModelHandle();
};

//private--start
inline void TARGET :: getRand(){
	x = (float)(((MAX_X-500.0f)-(MIN_X+500.0f)+1.0f)*((double)rand()/(double)(RAND_MAX+0.1f))+(MIN_X+500.0f));
	y = (float)(((MAX_Y-50.0f)-MIN_Y+1.0f)*((double)rand()/(double)(RAND_MAX+0.1f))+MIN_Y);
	z = (float)(((MAX_Z-500.0f)-(MIN_Z+500.0f)+1.0f)*((double)rand()/(double)(RAND_MAX+0.1f))+(MIN_Z+500.0f));
	rotate = (float)((2*PI+1.0f)*((double)rand()/(double)(RAND_MAX+0.1f)));
}
//private--end

//public--start
inline TARGET :: TARGET(void){
	srand((unsigned)time(NULL));
	ModelHandle = MV1LoadModel("model\\target\\target.mqo");
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
	MV1SetupCollInfo(ModelHandle, -1, 16, 16, 16);
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
//public--end