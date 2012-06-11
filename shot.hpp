#include "list.hpp"

class SHOT{
private:
	LIST s;
	int col;
public:
	//inline--start
	SHOT(int col);
	~SHOT(){}
	//表示
	void display();
	//移動
	void move();
	//弾の追加
	void newShot(VECTOR pos, float radius, float rotate, float v, int col);
	void newShot(VECTOR pos, float radius, float rotate, float v);
	void newShots(VECTOR pos1, VECTOR pos2, float radius, float rotate1, float rotate2, float v);
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
}

//移動
inline void SHOT :: move(){
	s.setHead();
	while(s.next()){
		if(s.get()->move()){
			s.deleteNode();
			s.pre();
		}
	}
}

//弾の追加
inline void SHOT :: newShot(VECTOR pos, float radius, float rotate, float v, int col){
	if(s.count() >= MAX_SHOT)
		return;
	s.newNODE(new SPHERE(pos, radius, rotate, v, col));
}

inline void SHOT :: newShot(VECTOR pos, float radius, float rotate, float v){
	if(s.count() >= MAX_SHOT)
		return;
	s.newNODE(new SPHERE(pos, radius, rotate, v, this->col));
}

inline void SHOT :: newShots(VECTOR pos1, VECTOR pos2, float radius, float rotate1, float rotate2, float v){
	if(s.count() >= MAX_SHOT-1)
		return;
	s.newNODE(new SPHERE(pos1, radius, rotate1, v, this->col));
	s.newNODE(new SPHERE(pos2, radius, rotate2, v, this->col));
}


//弾の削除
inline void SHOT :: delShot(){
	s.deleteNode();
}

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
			s.deleteNode();
		}
		MV1CollResultPolyDimTerminate(result);
	}
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
			s.deleteNode();
		}
		MV1CollResultPolyDimTerminate(result);
	}
	return count;
}
//public--end