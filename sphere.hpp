#include "DxLib.h"
#include <math.h>
#include "parameter.h"

class SPHERE{
private:
	float x, y, z;
	float rotateX, rotateY, rotateZ;
	float radius;
	float v;
	int col;
public:
	//inline--start
	//�R���X�g���N�^
	SPHERE(VECTOR pos, float radius, VECTOR rotate, float v, int col);
	//�ݒ�
	void set(VECTOR pos, float radius, VECTOR rotate, float v, int col);
	VECTOR getPos();
	//���a�擾
	float getRadius();
	//�\��
	void display(void);
	//�ړ�
	bool move(void);
};

//public--start
//�R���X�g���N�^
inline SPHERE :: SPHERE(VECTOR pos, float radius, VECTOR rotate, float v, int col){
	set(pos, radius, rotate, v, col);
}

//�ݒ�
inline void SPHERE :: set(VECTOR pos, float radius, VECTOR rotate, float v, int col){
	this->x = pos.x;
	this->y = pos.y;
	this->z = pos.z;
	this->radius = radius;
	this->rotateX = rotate.x;
	this->rotateY = rotate.y;
	this->rotateZ = rotate.z;
	this->v = v;
	this->col = col;

}

inline VECTOR SPHERE ::getPos(){
	return VGet(x, y ,z);
}

inline float SPHERE :: getRadius(){
	return radius;
}

inline void SPHERE :: display(void){
	//if(dflag)
		DrawSphere3D(VGet(x, y, z), radius, 16, col, col, TRUE);
}

//�ړ�
inline bool SPHERE :: move(void){
	bool flag=false;

	x -= v * sinf(rotateY);
	if(x > MAX_X){
		x = MAX_X;
		flag = true;
	}else if(x < MIN_X){
		x = MIN_X;
		flag = true;
	}

	y += v * sinf(rotateX/1.5f);
	if(y > MAX_Y){
		y = MAX_Y;
		flag = true;
	}else if(y < 0){
		y = 0;
		flag = true;
	}

	z -= v * cosf(rotateY);
	if(z > MAX_Z){
		z=MAX_Z;
		flag = true;
	}else if(z < MIN_Z){
		z=MIN_X;
		flag = true;
	}

	return flag;
}
//public--end