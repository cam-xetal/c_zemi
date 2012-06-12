#ifndef ENEMY_B
#define EMEMY_B

#include "DxLib.h"
#include <stdlib.h>
#include <time.h>
#include "model.hpp"

class ENEMY : public MODEL{
protected:
	bool fFlag;
	bool bFlag;
	bool upFlag;
	bool rRFlag;
	bool lRFlag;
	bool vFlag;
private:
	//inline--start
	float getRand();
	void displayHp();
	//void init();
	//inline--end
	void ai();
	void ai(VECTOR pV);
	void ai(float rotateY, VECTOR pV);
public:
	//inline--start
	ENEMY(VECTOR pos, float rotate, SHOT* mS);
	//ENEMY(VECTOR pos, float rotate, char* file, SHOT* mS);
	void display();
	void virtual control();
	void control(VECTOR pV);
	void control(float rotateY, VECTOR pV);
	//inline--end
};

//private--start
inline float ENEMY :: getRand(){
	return (float)rand()/((float)(RAND_MAX+0.1f));
}

/*
inline void ENEMY :: init(){
	srand((unsigned)time(NULL));
	fFlag = false;
	bFlag =false;
	upFlag = false;
	rRFlag = false;
	lRFlag = false;
	vFlag = false;
}*/

inline void ENEMY :: displayHp(){
	DrawBox(400, 45, 600, 65, GetColor(255, 125, 0), FALSE);
	DrawBox(400, 45, 400+hp*2, 65, GetColor(255, 125, 0), TRUE);
}
//private--end

//public--start
inline ENEMY :: ENEMY(VECTOR pos, float rotate, SHOT* mS) : MODEL(mS, rotate){
	srand((unsigned)time(NULL));
	fFlag = false;
	bFlag =false;
	upFlag = false;
	rRFlag = false;
	lRFlag = false;
	vFlag = false;
}

/*
inline ENEMY :: ENEMY(VECTOR pos, float rotate, char* file, SHOT* mS) : MODEL(file, mS, rotate){
	init();
}*/

inline void ENEMY :: display(){
	displayHp();
	MODEL :: display();
}

inline void ENEMY :: control(){
	ai();
	move(fFlag, bFlag, upFlag, rRFlag, lRFlag, vFlag);
	shot();
}

inline void ENEMY :: control(VECTOR pV){
	ai(pV);
	move(fFlag, bFlag, upFlag, rRFlag, lRFlag, vFlag);
	shot();
}

inline void ENEMY :: control(float rotateY, VECTOR pV){
	ai(rotateY, pV);
	move(fFlag, bFlag, upFlag, rRFlag, lRFlag, vFlag);
	shot();
}
//public--end

#endif