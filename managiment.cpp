#include "DxLib.h"
#include "managiment.h"
#include "player.h"
#include "enemy.h"
#include "target.h"

//FPS表示関数
void MANAGIMENT :: fpsDisplay(){
	static int time1=0, time2=0;
	static int count=0;
	static double fps=0.0;
	
	if(count == 0)
		time1=GetNowCount();	//1周目の時間取得
	
	if(count == 49){
		time2=GetNowCount();	//50周目の時間取得
		fps = 1000.0f/((time2-time1)/50.0f);	//FPSを計算
		count=0;
	}else
		count++;	//現在何周目かカウント
	
	if(fps != 0)
		DrawFormatString(565,460,0xffffffff,"FPS %.1f",fps);	//FPSを表示
	return;
}

int MANAGIMENT :: selectMode(void){
	int select = 0;
	int count = 0;
	Sleep(500);
	while(ProcessMessage() == 0){
		//画面をクリア
		ClearDrawScreen();
		//表示
		for(int i=0;i<4;i++){
			if(i == select)
				menu[i].displaySelect();
			else
				menu[i].displayNormal();
		}
		//入力
		if(count > 20){
			//下キー
			if(CheckHitKey(KEY_INPUT_DOWN)){
				++select%=4;
				count = 0;
			}
			//上キー
			if(CheckHitKey(KEY_INPUT_UP)){
				select--;
				if(select < 0)
					select+=4;
				count = 0;
			}
		}
		count++;
		//エンターキー
		if(CheckHitKey(KEY_INPUT_RETURN)){
			mode = select;
			return mode;
		}
		if(CheckHitKey(KEY_INPUT_ESCAPE)){
			mode = 3;
			return mode;
		}
		//裏画面の内容を表画面に反映
		ScreenFlip();
	}
	return 4;
}

void MANAGIMENT :: selectAction(void){
	switch(mode){
		case 0:
			freeMode();
			break;
		case 1:
			battleModeC();
			break;
		case 2:
			battleModeH();
			break;
	}
}

void MANAGIMENT :: freeMode(){
	int ModelHandle;
	//床読み込み
	ModelHandle = MV1LoadModel("model\\floor\\floor.mqo");

	//弾の配列の確保
	SHOT* mShot;
	mShot = new SHOT(GetColor(255, 255, 0));
	//モデルの読み込み
	PLAYER* p;
	p = new PLAYER(VGet(0, 0, 0), 0.0, mShot);
	//ターゲットの読み込み
	TARGET t;
	t.newTarget();

	while(ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		// 画面をクリア
		ClearDrawScreen();
		//ここから
		//床の描画
		MV1SetPosition(ModelHandle, VGet(0, 0, 0));
		MV1DrawModel(ModelHandle);
		//FPSの表示
		fpsDisplay();
		//カプセルの表示
		//DrawCapsule3D(VGet(320.0f, 100.0f, 0.0f), VGet(320.0f, 300.0f, 0.0f), 40.0f, 8, GetColor(0,255,0), GetColor(255,255,255), TRUE);
		//モデルの操作,描画
		p->control();
		p->display();
		t.display();
		if(mShot->collisionModel(t.getModelHandle()) > 0){
			t.delTarget();
			t.newTarget();
		}
		//ここまで
		//裏画面の内容を表画面に反映
		ScreenFlip();
	}
	MV1DeleteModel(ModelHandle);
	delete mShot;
	delete p;
}
void MANAGIMENT :: battleModeC(){
	int ModelHandle;
	//床読み込み
	ModelHandle = MV1LoadModel("model\\floor\\floor.mqo");
	MV1SetPosition(ModelHandle, VGet(0, 0, 0));

	//弾の配列の確保
	SHOT* mShot;
	SHOT* eShot;
	mShot = new SHOT(GetColor(255, 255, 0));
	eShot = new SHOT(GetColor(255, 0, 0));
	//モデルの読み込み
	PLAYER* p;
	ENEMY* e;
	p = new PLAYER(VGet(0, 0, 2000.0), 0.0f, mShot);
	e = new ENEMY(VGet(0, 0, -2000), PI, eShot);
	//ターゲットの読み込み
	TARGET t;
	t.newTarget();

	while(ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		// 画面をクリア
		ClearDrawScreen();
		//ここから
		//床の描画
		MV1DrawModel(ModelHandle);
		//FPSの表示
		fpsDisplay();
		//カプセルの表示
		//DrawCapsule3D(VGet(320.0f, 100.0f, 0.0f), VGet(320.0f, 300.0f, 0.0f), 40.0f, 8, GetColor(0,255,0), GetColor(255,255,255), TRUE);
		//モデルの操作,描画
		//プレイヤー
		p->control();
		p->display();
		//敵
		e->control(p->getRotateY(), p->getVector());
		e->display();
		/*
		//的
		t.display();
		if(mShot->collisionModel(t.getModelHandle())){
			t.delTarget();
			t.newTarget();
		}
		*/
		if(p->damageCheck(eShot) <= 0)
			break;
		if(e->damageCheck(mShot) <= 0)
			break;
		mShot->collisionModel(e->getModelHandle());
		eShot->collisionModel(p->getModelHandle());
		//ここまで
		//裏画面の内容を表画面に反映
		ScreenFlip();
	}
	while(ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		// 画面をクリア
		ClearDrawScreen();
		//床の描画
		MV1DrawModel(ModelHandle);
		//FPSの表示
		fpsDisplay();
		p->addCR(0.01f);
		p->display();
		e->display();
		//裏画面の内容を表画面に反映
		ScreenFlip();
	}
		
	MV1DeleteModel(ModelHandle);
	delete mShot;
	delete eShot;
	delete p;
	delete e;
}