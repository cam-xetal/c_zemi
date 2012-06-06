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
	void read(char* src_ip, int* src_port, char* sin_ip, int* sin_port){
		char tmp[32];
		fscanf_s(fp, "%s\n", tmp, 32); 
		fscanf_s(fp, "ip = %s\n", src_ip, 15);
		fscanf_s(fp, "port = %d\n", src_port);
		fscanf_s(fp, "%s\n", tmp, 32);
		fscanf_s(fp, "ip = %s\n", sin_ip, 15);
		fscanf_s(fp, "port = %d", sin_port);
	}

	~READ_INIT(){
		fclose(fp);
	}
};