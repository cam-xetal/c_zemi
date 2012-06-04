#include <process.h>
//#include "DxLib.h"
#include "net_trans.h"
#include "menu.h"

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
	menu[0].set(80, 200, "フリーモード");
	menu[1].set(80, 250, "対戦(COM)");
	menu[2].set(80, 300, "対戦(対人)");
	menu[3].set(80, 350, "終了");
}

inline void MANAGIMENT :: init(void){
	//バックグラウンドの設定
	SetBackgroundColor(0, 128, 255);
	//ウィンドウの設定
	ChangeWindowMode(TRUE);
	//ＤＸライブラリの初期化
	if(DxLib_Init() < 0){
		exit(1);
	}
	//描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	//ライト指定
	ChangeLightTypeDir(VGet(1.0, -1.0, 0.0));
	CreateDirLightHandle(VGet(-1.0, 1, 0));
	//Zバッファ設定
	//Zバッファ使用
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
}


//public--end