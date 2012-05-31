//#include "sphere.h"
#include "list.h"

class SHOT{
private:
	LIST s;
	int col;
public:
	//inline--start
	SHOT(int col);
	//•\Ž¦
	void display();
	//ˆÚ“®
	void move();
	//’e‚Ì’Ç‰Á
	void newShot(VECTOR pos, float radius, float rotate, float v, int col);
	void newShot(VECTOR pos, float radius, float rotate, float v);
	//’e‚Ìíœ
	void delShot();
	//void delShot(int index);
	//“–‚½‚è”»’è
	int collisionModel(int ModelHandle);
	int collisionTarget(int ModelHandle);
	//inline--end
};

//public--start
inline SHOT :: SHOT(int col){
	this->col = col;
}

//•\Ž¦
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

//ˆÚ“®
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

//’e‚Ì’Ç‰Á
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

//’e‚Ìíœ
inline void SHOT :: delShot(){
	s.deleteNode();
}
/*
inline void SHOT :: delShot(int index){
	s[index].setFlag(false);
}*/

//“–‚½‚è”»’è
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
			if(!s.deleteNode())
				break;
		}
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

//“–‚½‚è”»’è
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
			if(!s.deleteNode())
				break;
		}
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