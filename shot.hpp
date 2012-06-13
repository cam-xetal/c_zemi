#include "list.hpp"

class SHOT{
private:
	LIST s;
	int col;
	float radius;
	float v;
public:
	//inline--start
	SHOT(int col, float radius, float v);
	~SHOT(){}
	//�\��
	void display();
	//�ړ�
	void move();
	//�e�̒ǉ�
	void newShot(VECTOR pos, VECTOR rotate);
	void newShots(VECTOR pos1, VECTOR pos2, VECTOR rotate1, VECTOR rotate2);
	//�e�̍폜
	void delShot();
	//void delShot(int index);
	//�����蔻��
	int collisionModel(int ModelHandle);
	int collisionTarget(int ModelHandle);
	//inline--end
};

//public--start
inline SHOT :: SHOT(int col, float radius, float v){
	this->col = col;
	this->radius = radius;
	this->v = v;
}

//�\��
inline void SHOT :: display(){
	s.setHead();
	while(s.next()){
		s.get()->display();
	}
}

//�ړ�
inline void SHOT :: move(){
	s.setHead();
	while(s.next()){
		if(s.get()->move()){
			s.deleteNode();
			//s.pre();
		}
	}
}

//�e�̒ǉ�
inline void SHOT :: newShot(VECTOR pos, VECTOR rotate){
	if(s.count() >= MAX_SHOT)
		return;
	s.newNODE(new SPHERE(pos, this->radius, rotate, this->v, this->col));
}

inline void SHOT :: newShots(VECTOR pos1, VECTOR pos2, VECTOR rotate1, VECTOR rotate2){
	if(s.count() >= MAX_SHOT-1)
		return;
	s.newNODE(new SPHERE(pos1, this->radius, rotate1, this->v, this->col));
	s.newNODE(new SPHERE(pos2, this->radius, rotate2, this->v, this->col));
}


//�e�̍폜
inline void SHOT :: delShot(){
	s.deleteNode();
}

//�����蔻��
inline int SHOT :: collisionModel(int ModelHandle){
	MV1_COLL_RESULT_POLY_DIM result;
	SPHERE* tmp;
	int count = 0;
	s.setHead();
	while(s.next()){
		tmp = s.get();
		result = MV1CollCheck_Sphere(ModelHandle, 39, tmp->getPos(), tmp->getRadius());
		if(result.HitNum > 0){
			count++;
			s.deleteNode();
		}
		MV1CollResultPolyDimTerminate(result);
	}
	return count;
}

//�����蔻��
inline int SHOT :: collisionTarget(int ModelHandle){
	MV1_COLL_RESULT_POLY_DIM result;
	SPHERE* tmp;
	int count = 0;
	s.setHead();
	while(s.next()){
		tmp = s.get();
		result = MV1CollCheck_Sphere(ModelHandle, -1, tmp->getPos(), tmp->getRadius());
		if(result.HitNum > 0){
			count++;
			s.deleteNode();
		}
		MV1CollResultPolyDimTerminate(result);
	}
	return count;
}
//public--end