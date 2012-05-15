#include "DxLib.h"
#include "model.h"

class PLAYER : public MODEL{
private:
	int col;
	float cx, cy, cz;
	float cRotate;
	//inline--start
	void init(void);
	void displayXYZ(void);
	void displayV(void);
	//inline--end
public:
	//inline--start
	PLAYER(VECTOR pos, float rotate, SHOT* mS);
	PLAYER(VECTOR pos, float rotate, char* file, SHOT* mS);
	void addCR(float cr);
	//inline--end
	void display();
	void control();
};

//private--start
inline void PLAYER :: init(void){
	x = y = z =0;
	x0 = z0 = 0;
	y0 = 100.0;
	cRotate = 0;
	v = 0;
}

inline void PLAYER :: displayXYZ(void){
	int col = GetColor(255, 255, 255);
	DrawFormatString(10, 10, col, "x:%.1f, y:%.1f, z:%.1f", x, y, z);
}

inline void PLAYER :: displayV(void){
	int col = GetColor(255, 255, 255);
	VECTOR speed = VSub(VGet(x, y, z), VGet(preX, preY, preZ));
	DrawFormatString(10, 40,  col, "‘¬“x:%.1f", VSize(speed)*10.0f/3.0f);
}
//private--end

//public--start
inline PLAYER :: PLAYER(VECTOR pos, float rotate, SHOT* mS) : MODEL(mS, rotate){
	init();
	this->x = pos.x;
	this->y = pos.y;
	this->z = pos.z;
}

inline PLAYER :: PLAYER(VECTOR pos, float rotate, char* file, SHOT* mS) : MODEL(file, mS, rotate){
	init();
	this->x = pos.x;
	this->y = pos.y;
	this->z = pos.z;
}

inline void PLAYER :: addCR(float cr){
	cRotate += cr;
	if(cRotate > 2*PI)
		cRotate -= 2*PI;
	cx = x + x0 + 800*sinf(cRotate);
	cy = y + y0 + 150.0f;
	cz = z + z0 + 800*cosf(cRotate);
}
//public--end