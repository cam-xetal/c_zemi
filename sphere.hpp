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
	//コンストラクタ
	//配列用
	SPHERE(void);
	//単体呼び出し用
	SPHERE(VECTOR pos, float radius, float rotate, float v, int col);
	//設定
	void set(VECTOR pos, float radius, float rotate, float v, int col, bool dflag);
	//位置設定
	void setPos(float x, float y, float z);
	//位置取得
	void getPos(float* x, float* y, float* z);
	VECTOR getPos();
	//半径設定
	void setRadius(float r);
	//半径設定
	void setRadius(float* r);
	//半径取得
	float getRadius();
	//色設定
	void setColor(int col);
	//向き設定
	void setRotate(float rotate);
	//向き取得
	void getRotate(float* rotate);
	//速度設定
	void setV(float v);
	//速度取得
	void getV(float* v);
	/*
	//描画フラグ設定
	void setFlag(bool flag);
	//描画フラグ取得
	bool getFlag();
	*/
	//表示
	void display(void);
	//移動
	bool move(void);
	//inline--end
};

//public--start
//コンストラクタ
//配列用
inline SPHERE :: SPHERE(void){
	dflag = false;
}

//単体呼び出し用
inline SPHERE :: SPHERE(VECTOR pos, float radius, float rotate, float v, int col){
	set(pos, radius, rotate, v, col, true);
}

//設定
inline void SPHERE :: set(VECTOR pos, float radius, float rotate, float v, int col, bool dflag){
	setPos(pos.x, pos.y, pos.z);
	setRadius(radius);
	setRotate(rotate);
	setV(v);
	setColor(col);
	//setFlag(dflag);
}

//位置設定
inline void SPHERE :: setPos(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
}

//位置取得
inline void SPHERE :: getPos(float* x, float* y, float* z){
	*x = this->x;
	*y = this->y;
	*z = this->z;
}

inline VECTOR SPHERE ::getPos(){
	return VGet(x, y ,z);
}

//半径設定
inline void SPHERE :: setRadius(float r){
	this->radius = r;
}

//半径取得
inline void SPHERE :: setRadius(float* r){
	*r = this->radius;
}

//半径設定
inline float SPHERE :: getRadius(){
	return radius;
}

//色設定
inline void SPHERE :: setColor(int col){
	this->col = col;
}

//向き設定
inline void SPHERE :: setRotate(float rotate){
	this->rotate = rotate;
}

//向き取得
inline void SPHERE :: getRotate(float* rotate){
	*rotate = this->rotate;
}

//速度設定
inline void SPHERE :: setV(float v){
	this->v = v;
}

//速度取得
inline void SPHERE :: getV(float* v){
	*v = this->v;
}

/*
//描画フラグ設定
inline void SPHERE :: setFlag(bool flag){
	this->dflag = flag;
}

//描画フラグ取得
inline bool SPHERE :: getFlag(){
	return this->dflag;
}*/

//表示
inline void SPHERE :: display(void){
	//if(dflag)
		DrawSphere3D(VGet(x, y, z), radius, 16, col, col, TRUE);
}

//移動
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