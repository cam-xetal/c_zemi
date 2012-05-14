#include "sphere.h"

class SHOT{
private:
	SPHERE s[MAX_SHOT];
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
	void delShot(int index);
	//�����蔻��
	int collisionModel(int ModelHandle);
	//inline--end
};

//public--start
inline SHOT :: SHOT(int col){
	this->col = col;
}

//�\��
inline void SHOT :: display(){
	for(int i=0;i<MAX_SHOT;i++){
		if(s[i].getFlag()){
			s[i].display();
		}
	}
}

//�ړ�
inline void SHOT :: move(){
	for(int i=0;i<MAX_SHOT;i++){
		if(s[i].getFlag()){
			if(s[i].move())
				delShot(i);
		}
	}
}

//�e�̒ǉ�
inline void SHOT :: newShot(VECTOR pos, float radius, float rotate, float v, int col){
	for(int i=0;i<MAX_SHOT;i++){
		if(!s[i].getFlag()){
			s[i].set(pos, radius, rotate, v, col, true);
			return;
		}
	}
}

inline void SHOT :: newShot(VECTOR pos, float radius, float rotate, float v){
	for(int i=0;i<MAX_SHOT;i++){
		if(!s[i].getFlag()){
			s[i].set(pos, radius, rotate, v, this->col, true);
			return;
		}
	}
}

//�e�̍폜
inline void SHOT :: delShot(int index){
	s[index].setFlag(false);
}

//�����蔻��
inline int SHOT :: collisionModel(int ModelHandle){
	MV1_COLL_RESULT_POLY_DIM result;
	int count = 0;
	for(int i=0;i<MAX_SHOT;i++){
		if(s[i].getFlag()){
			result = MV1CollCheck_Sphere(ModelHandle, 39, s[i].getPos(), s[i].getRadius());
			if(result.HitNum >= 1){
				s[i].setFlag(false);
				count++;
			}
		}
	}
	return count;
}
//public--end