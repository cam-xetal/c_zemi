#include "DxLib.h"
#include <math.h>

class BUILDING{
private:
	int ModelHandle;
public:
	BUILDING();
	BUILDING(VECTOR pos);
	~BUILDING();
	int getModelHandle();
	void display();
	bool collision(VECTOR pos, VECTOR rotate);
};

inline bool BUILDING :: collision(VECTOR pos, VECTOR rotate){
	MV1_COLL_RESULT_POLY_DIM  result;
	VECTOR pos1 = VGet(pos.x+600*sinf(rotate.y), pos.y+100.0f+200.0f-500*sinf(rotate.x), pos.z+600*cosf(rotate.y));
	VECTOR pos2 = VGet(pos.x-200*sinf(rotate.y), pos.y+100.0f+200.0f+500*sinf(rotate.x), pos.z-200*cosf(rotate.y));
	result = MV1CollCheck_Capsule(ModelHandle, -1, pos1, pos2, 280.0f);

	if(result.HitNum > 0){
		MV1CollResultPolyDimTerminate(result);
		return true;
	}
	MV1CollResultPolyDimTerminate(result);

	return false;
}
