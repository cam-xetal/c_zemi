#include "DxLib.h"
#include "managiment.hpp"
#include "player.hpp"
#include "enemy_net.hpp"
#include "target.hpp"

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
	MV1SetScale(ModelHandle, VGet(1.5f, 0, 1.5f));
	MV1SetPosition(ModelHandle, VGet(0, 0, 0));

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
		MV1DrawModel(ModelHandle);
		//FPSの表示
		fpsDisplay();
		//モデルの操作,描画
		p->control();
		p->display();
		t.display();
		if(mShot->collisionTarget(t.getModelHandle()) > 0){
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
	MV1SetScale(ModelHandle, VGet(1.5f, 0, 1.5f));
	MV1SetPosition(ModelHandle, VGet(0, 0, 0));

	//弾の配列の確保
	SHOT* mShot;
	SHOT* eShot;
	mShot = new SHOT(GetColor(255, 255, 0));
	eShot = new SHOT(GetColor(255, 0, 0));
	//モデルの読み込み
	PLAYER* p;
	ENEMY* e;
	p = new PLAYER(VGet(0, 0, 4000.0), 0.0f, mShot);
	e = new ENEMY(VGet(0, 0, -4000), PI, eShot);

	while(ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		// 画面をクリア
		ClearDrawScreen();
		//ここから
		//床の描画
		MV1DrawModel(ModelHandle);
		//FPSの表示
		fpsDisplay();
		//モデルの操作,描画
		//プレイヤー
		p->control();
		p->display();
		//敵
		e->control(p->getRotateY(), p->getVector());
		e->display();
		
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
	int pH;
	int eH;
	while(ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		// 画面をクリア
		ClearDrawScreen();
		//床の描画
		MV1DrawModel(ModelHandle);
		//FPSの表示
		SetFontSize(16);
		fpsDisplay();
		p->addCR(0.01f);
		p->display();
		e->display();
		SetFontSize(32);
		pH = p->getHp();
		eH = e->getHp();
		if(pH == eH)
			DrawFormatString(300, 350, GetColor(255, 255, 255), "Draw");
		else if(pH > eH) 
			DrawFormatString(310, 350, GetColor(255, 255, 255), "Win");
		else
			DrawFormatString(300, 350, GetColor(255, 255, 255), "Loss");
		//裏画面の内容を表画面に反映
		ScreenFlip();
	}
	SetFontSize(16);

	MV1DeleteModel(ModelHandle);
	delete mShot;
	delete eShot;
	delete p;
	delete e;
}

void MANAGIMENT :: battleModeH(){
	int ModelHandle;
	//床読み込み
	ModelHandle = MV1LoadModel("model\\floor\\floor.mqo");
	MV1SetScale(ModelHandle, VGet(1.5f, 0, 1.5f));
	MV1SetPosition(ModelHandle, VGet(0, 0, 0));

	//弾の配列の確保
	SHOT* mShot;
	SHOT* eShot;
	mShot = new SHOT(GetColor(255, 255, 0));
	eShot = new SHOT(GetColor(255, 0, 0));

	
	READ_INIT* read;
	read = new READ_INIT();
	char src_ip[32];
	int src_port;
	char sin_ip[32];
	int sin_port;
	read->read(src_ip, &src_port, sin_ip, &sin_port);
	delete read;
	
	NET_TRANS* net;
	net = new NET_TRANS(src_ip, src_port, sin_ip, sin_port);
	net->setBind();
	

	hTh = (HANDLE)_beginthreadex(NULL, 0, &thread_recv, net, 0, &thID);
	ResumeThread(hTh);
	net->flag1 = false;
	net->flag2 = false;
	while(1){
		DrawFormatString(20, 20, GetColor(0, 0, 0), "通信中");
		if(!net->flag2)
			net->send("start");
		if(net->flag1)
			net->send("ok");
		if(net->flag1 && net->flag2)
			break;
		if(ProcessMessage() != 0 || CheckHitKey(KEY_INPUT_ESCAPE) != 0){
			TerminateThread(hTh, 0);
			delete net;
			delete mShot;
			delete eShot;
			MV1DeleteModel(ModelHandle);
			return;
		}
		ScreenFlip();
	}
	TerminateThread(hTh, 0);
	
	//モデルの読み込み
	PLAYER* p;
	ENEMY_NET* e;
	p = new PLAYER(VGet(0, 0, 4000.0), 0.0f, mShot, net);
	e = new ENEMY_NET(VGet(0, 0, -4000), PI, eShot, net);
	e->start(e);

	int pH;
	int eH;

	while(ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		// 画面をクリア
		ClearDrawScreen();
		//床の描画
		MV1DrawModel(ModelHandle);
		//FPSの表示
		fpsDisplay();
		//モデルの操作,描画
		//プレイヤー
		p->control();
		p->display();
		p->send();
		//敵
		e->enterCritical();
		e->display();
		pH = p->damageCheck(eShot);
		eH = e->damageCheck(mShot);
		if(pH <= 0 || eH <= 0){
			e->leaveCritical();
			break;
		}
		mShot->collisionModel(e->getModelHandle());
		eShot->collisionModel(p->getModelHandle());
		e->leaveCritical();
		//裏画面の内容を表画面に反映
		ScreenFlip();
	}
	
	
	while(ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		p->send();
		// 画面をクリア
		ClearDrawScreen();
		//床の描画
		MV1DrawModel(ModelHandle);
		//FPSの表示
		SetFontSize(16);
		fpsDisplay();
		p->addCR(0.01f);
		p->display();
		e->display();

		SetFontSize(32);
		pH = p->getHp();
		eH = e->getHp();
		if(pH == eH)
			DrawFormatString(300, 350, GetColor(255, 255, 255), "Draw");
		else if(pH > eH) 
			DrawFormatString(310, 350, GetColor(255, 255, 255), "Win");
		else
			DrawFormatString(300, 350, GetColor(255, 255, 255), "Loss");
		//裏画面の内容を表画面に反映
		ScreenFlip();
	}
	e->stop();
	SetFontSize(16);
	
	
	//delete net;

	MV1DeleteModel(ModelHandle);
	delete mShot;
	delete eShot;
	delete p;
	delete e;
}