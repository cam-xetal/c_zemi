#include "DxLib.h"
#include <string.h>
#include "parameter.h"

class MENU{
private:
	int x, y;
	char str[MAX_STR];
public:
	//inline--start
	void set(int x, int y, char* str);
	void setPos(int x, int y);
	void setStr(char* str);
	void displayNormal();
	void displaySelect();
	//inline--end
};

//public--start
inline void MENU :: set(int x, int y, char* str){
	setPos(x, y);
	setStr(str);
}

inline void MENU :: setPos(int x, int y){
	this->x = x;
	this->y = y;
}

inline void MENU :: setStr(char* str){
	strcpy_s(this->str, str);
}

inline void MENU :: displayNormal(){
	DrawString(x, y, str, GetColor(255, 255, 255), TRUE);
}

inline void MENU :: displaySelect(){
	DrawString(x+20, y, str, GetColor(255, 255, 255), TRUE);
}
//public--end