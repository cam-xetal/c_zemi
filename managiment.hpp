#include <process.h>
#include "net_trans.hpp"
#include "menu.hpp"

class MANAGIMENT{
private:
	int mode;
	MENU menu[5];
	unsigned int thID;
	HANDLE hTh;

	void fpsDisplay();
	static unsigned __stdcall thread_recv(void* param){
		char str[16];
		NET_TRANS* net = (NET_TRANS*)param;
		while(1){
			net->recv(str);
			if(strncmp(str, "start", 5) == 0){
				net->flag1 = true;
			}
			if(strncmp(str, "ok", 2) == 0){
				net->flag1 = true;
				net->flag2 = true;
			}
		}
		return 0;
	}
public:
	//inline--start
	MANAGIMENT(void);
	void init(void);
	void startTh(NET_TRANS* net);
	void stopTh();
	//inline--end
	int selectMode(void);
	void selectAction(void);
	void freeMode();
	void battleModeC();
	void battleModeH();
};

//public--start
inline MANAGIMENT :: MANAGIMENT(void){
	int mode=0;
	menu[0].set(80, 200, "�t���[���[�h");
	menu[1].set(80, 250, "�ΐ�(COM)");
	menu[2].set(80, 300, "�ΐ�(�ΐl)");
	menu[3].set(80, 350, "�I��");
}

inline void MANAGIMENT :: init(void){
	//�o�b�N�O���E���h�̐ݒ�
	SetBackgroundColor(0, 128, 255);
	//�E�B���h�E�̐ݒ�
	ChangeWindowMode(TRUE);
	//�c�w���C�u�����̏�����
	if(DxLib_Init() < 0){
		exit(1);
	}
	//�`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	//���C�g�w��
	ChangeLightTypeDir(VGet(1.0, -1.0, 0.0));
	CreateDirLightHandle(VGet(-1.0, 1, 0));
	//Z�o�b�t�@�ݒ�
	//Z�o�b�t�@�g�p
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
}


//public--end