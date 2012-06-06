#include "DxLib.h"
#include <math.h>
#include "parameter.h"

class SPHERE{
private:
	float x, y, z;
	float rotate;
	float radius;
	float v;
	int col;
	bool dflag;
public:
	//inline--start
	//�R���X�g���N�^
	//�z��p
	SPHERE(void);
	//�P�̌Ăяo���p
	SPHERE(VECTOR pos, float radius, float rotate, float v, int col);
	//�ݒ�
	void set(VECTOR pos, float radius, float rotate, float v, int col, bool dflag);
	//�ʒu�ݒ�
	void setPos(float x, float y, float z);
	//�ʒu�擾
	void getPos(float* x, float* y, float* z);
	VECTOR getPos();
	//���a�ݒ�
	void setRadius(float r);
	//���a�ݒ�
	void setRadius(float* r);
	//���a�擾
	float getRadius();
	//�F�ݒ�
	void setColor(int col);
	//�����ݒ�
	void setRotate(float rotate);
	//�����擾
	void getRotate(float* rotate);
	//���x�ݒ�
	void setV(float v);
	//���x�擾
	void getV(float* v);
	/*
	//�`��t���O�ݒ�
	void setFlag(bool flag);
	//�`��t���O�擾
	bool getFlag();
	*/
	//�\��
	void display(void);
	//�ړ�
	bool move(void);
	//inline--end
};

//public--start
//�R���X�g���N�^
//�z��p
inline SPHERE :: SPHERE(void){
	dflag = false;
}

//�P�̌Ăяo���p
inline SPHERE :: SPHERE(VECTOR pos, float radius, float rotate, float v, int col){
	set(pos, radius, rotate, v, col, true);
}

//�ݒ�
inline void SPHERE :: set(VECTOR pos, float radius, float rotate, float v, int col, bool dflag){
	setPos(pos.x, pos.y, pos.z);
	setRadius(radius);
	setRotate(rotate);
	setV(v);
	setColor(col);
	//setFlag(dflag);
}

//�ʒu�ݒ�
inline void SPHERE :: setPos(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
}

//�ʒu�擾
inline void SPHERE :: getPos(float* x, float* y, float* z){
	*x = this->x;
	*y = this->y;
	*z = this->z;
}

inline VECTOR SPHERE ::getPos(){
	return VGet(x, y ,z);
}

//���a�ݒ�
inline void SPHERE :: setRadius(float r){
	this->radius = r;
}

//���a�擾
inline void SPHERE :: setRadius(float* r){
	*r = this->radius;
}

//���a�ݒ�
inline float SPHERE :: getRadius(){
	return radius;
}

//�F�ݒ�
inline void SPHERE :: setColor(int col){
	this->col = col;
}

//�����ݒ�
inline void SPHERE :: setRotate(float rotate){
	this->rotate = rotate;
}

//�����擾
inline void SPHERE :: getRotate(float* rotate){
	*rotate = this->rotate;
}

//���x�ݒ�
inline void SPHERE :: setV(float v){
	this->v = v;
}

//���x�擾
inline void SPHERE :: getV(float* v){
	*v = this->v;
}

/*
//�`��t���O�ݒ�
inline void SPHERE :: setFlag(bool flag){
	this->dflag = flag;
}

//�`��t���O�擾
inline bool SPHERE :: getFlag(){
	return this->dflag;
}*/

//�\��
inline void SPHERE :: display(void){
	//if(dflag)
		DrawSphere3D(VGet(x, y, z), radius, 16, col, col, TRUE);
}

//�ړ�
inline bool SPHERE :: move(void){
	bool flag=false;
	x -= v * sinf(rotate);
	if(x > MAX_X){
		x=MAX_X;
		flag = true;
	}else if(x < MIN_X){
		x=MIN_X;
		flag = true;
	}
	z -= v * cosf(rotate);
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