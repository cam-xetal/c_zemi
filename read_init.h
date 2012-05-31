#include <stdio.h>
#include <stdlib.h>

class READ_INIT{
private:
	FILE *fp;
public:
	READ_INIT(){
		if(fopen_s(&fp, "setting.ini", "r")  != 0)
			exit(1);
	}
	void read(char* ip, int* port){
		fscanf_s(fp, "ip : %s\n", ip, 15);
		fscanf_s(fp, "port : %d", port);
	}

	~READ_INIT(){
		fclose(fp);
	}
};