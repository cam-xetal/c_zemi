#include <stdio.h>
#include <stdlib.h>
#include "DxLib.h"

class READ_INIT{
private:
	FILE *fp;
public:
	READ_INIT();
	~READ_INIT();
	void read(char* src_ip, int* src_port, char* sin_ip, int* sin_port, VECTOR* pPos, VECTOR* ePos, float* pR, float* eR);
};

inline READ_INIT :: READ_INIT(){
	if(fopen_s(&fp, "setting.ini", "r")  != 0)
		exit(1);
}
inline READ_INIT ::	~READ_INIT(){
	fclose(fp);
}