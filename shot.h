//#include "sphere.h"
#include "list.h"

class SHOT{
private:
	LIST s;
	int col;
public:
	//inline--start
	SHOT(int col);
	//表示
	void display();
	//移動
	void move();
	//弾の追加
	void newShot(VECTOR pos, float radius, float rotate, float v, int col);
	void newShot(VECTOR pos, float radius, float rotate, float v);
	//弾の削除
	void delShot();
	//void delShot(int index);
	//当たり判定
	int collisionModel(int ModelHandle);
	int collisionTarget(int ModelHandle);
	//inline--end
};

//public--start
inline SHOT :: SHOT(int col){
	this->col = col;
}

//表示
inline void SHOT :: display(){
	s.setHead();
	while(s.next()){
		s.get()->display();
	}
	/*for(int i=0;i<MAX_SHOT;i++){
		if(s[i].getFlag()){
			s[i].display();
		}
	}*/
}

//移動
inline void SHOT :: move(){
	s.setHead();
	while(s.next()){
		if(s.get()->move()){
			if(!s.deleteNode())
				break;
		}
	}
	/*
	for(int i=0;i<MAX_SHOT;i++){
		if(s[i].getFlag()){
			if(s[i].move())
				delShot(i);
		}
	}*/
}

//弾の追加
inline void SHOT :: newShot(VECTOR pos, float radius, float rotate, float v, int col){
	if(s.count() > MAX_SHOT)
		return;
	s.newNODE(new SPHERE(pos, radius, rotate, v, col));
	/*for(int i=0;i<MAX_SHOT;i++){
		if(!s[i].getFlag()){
			s[i].set(pos, radius, rotate, v, col, true);
			return;
		}
	}*/
}

inline void SHOT :: newShot(VECTOR pos, float radius, float rotate, float v){
	if(s.count() > MAX_SHOT)
		return;
	s.newNODE(new SPHERE(pos, radius, rotate, v, this->col));
	/*
	for(int i=0;i<MAX_SHOT;i++){
		if(!s[i].getFlag()){
			s[i].set(pos, radius, rotate, v, this->col, true);
			return;
		}
	}*/
}

//弾の削除
inline void SHOT :: delShot(){
	s.deleteNode();
}
/*
inline void SHOT :: delShot(int index){
	s[index].setFlag(false);
}*/

//当たり判定
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
	/*
	for(int i=0;i<MAX_SHOT;i++){
		if(s[i].getFlag()){
			result = MV1CollCheck_Sphere(ModelHandle, 39, s[i].getPos(), s[i].getRadius());
			if(result.HitNum >= 1){
				s[i].setFlag(false);
				count++;
			}
		}
	}*/
	return count;
}

//当たり判定
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
	/*
	for(int i=0;i<MAX_SHOT;i++){
		if(s[i].getFlag()){
			result = MV1CollCheck_Sphere(ModelHandle, -1, s[i].getPos(), s[i].getRadius());
			if(result.HitNum >= 1){
				s[i].setFlag(false);
				count++;
			}
		}
	}*/
	return count;
}
//public--end