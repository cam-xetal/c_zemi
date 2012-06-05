//#include "sphere.h"
#include "list.h"

class SHOT{
private:
	LIST s;
	int col;
public:
	//inline--start
	SHOT(int col);
	//�\��
	void display();
	//�ړ�
	void move();
	//�e�̒ǉ�
	void newShot(VECTOR pos, float radius, float rotate, float v, int col);
	void newShot(VECTOR pos, float radius, float rotate, float v);
	//�e�̍폜
	void delShot();
	//void delShot(int index);
	//�����蔻��
	int collisionModel(int ModelHandle);
	int collisionTarget(int ModelHandle);
	//inline--end
};

//public--start
inline SHOT :: SHOT(int col){
	this->col = col;
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
			if(!s.deleteNode())
				break;
		}
	}
}

//�e�̒ǉ�
inline void SHOT :: newShot(VECTOR pos, float radius, float rotate, float v, int col){
	if(s.count() > MAX_SHOT)
		return;
	s.newNODE(new SPHERE(pos, radius, rotate, v, col));
}

inline void SHOT :: newShot(VECTOR pos, float radius, float rotate, float v){
	if(s.count() > MAX_SHOT)
		return;
	s.newNODE(new SPHERE(pos, radius, rotate, v, this->col));
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
			if(!s.deleteNode()){
				MV1CollResultPolyDimTerminate(result);
				break;
			}
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
			if(!s.deleteNode()){
				MV1CollResultPolyDimTerminate(result);
				break;
			}
		}
		MV1CollResultPolyDimTerminate(result);
	}
	return count;
}
//public--end