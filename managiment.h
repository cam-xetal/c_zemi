#include "DxLib.h"
#include "menu.h"

class MANAGIMENT{
private:
	int mode;
	MENU menu[5];
	void fpsDisplay();
public:
	//inline--start
	MANAGIMENT(void);
	void init(void);
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