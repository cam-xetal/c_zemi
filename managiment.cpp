#include "DxLib.h"
#include "managiment.h"
#include "player.h"
//#include "enemy.h"
#include "enemy_net.h"
#include "target.h"

//FPS�\���֐�
void MANAGIMENT :: fpsDisplay(){
	static int time1=0, time2=0;
	static int count=0;
	static double fps=0.0;
	
	if(count == 0)
		time1=GetNowCount();	//1���ڂ̎��Ԏ擾
	
	if(count == 49){
		time2=GetNowCount();	//50���ڂ̎��Ԏ擾
		fps = 1000.0f/((time2-time1)/50.0f);	//FPS���v�Z
		count=0;
	}else
		count++;	//���݉����ڂ��J�E���g
	
	if(fps != 0)
		DrawFormatString(565,460,0xffffffff,"FPS %.1f",fps);	//FPS��\��
	return;
}

int MANAGIMENT :: selectMode(void){
	int select = 0;
	int count = 0;
	Sleep(500);
	while(ProcessMessage() == 0){
		//��ʂ��N���A
		ClearDrawScreen();
		//�\��
		for(int i=0;i<4;i++){
			if(i == select)
				menu[i].displaySelect();
			else
				menu[i].displayNormal();
		}
		//����
		if(count > 20){
			//���L�[
			if(CheckHitKey(KEY_INPUT_DOWN)){
				++select%=4;
				count = 0;
			}
			//��L�[
			if(CheckHitKey(KEY_INPUT_UP)){
				select--;
				if(select < 0)
					select+=4;
				count = 0;
			}
		}
		count++;
		//�G���^�[�L�[
		if(CheckHitKey(KEY_INPUT_RETURN)){
			mode = select;
			return mode;
		}
		if(CheckHitKey(KEY_INPUT_ESCAPE)){
			mode = 3;
			return mode;
		}
		//����ʂ̓��e��\��ʂɔ��f
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
	//���ǂݍ���
	ModelHandle = MV1LoadModel("model\\floor\\floor.mqo");
	MV1SetScale(ModelHandle, VGet(1.5f, 0, 1.5f));
	MV1SetPosition(ModelHandle, VGet(0, 0, 0));

	//�e�̔z��̊m��
	SHOT* mShot;
	mShot = new SHOT(GetColor(255, 255, 0));
	//���f���̓ǂݍ���
	PLAYER* p;
	p = new PLAYER(VGet(0, 0, 0), 0.0, mShot);
	//�^�[�Q�b�g�̓ǂݍ���
	TARGET t;
	t.newTarget();

	while(ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		// ��ʂ��N���A
		ClearDrawScreen();
		//��������
		//���̕`��
		MV1DrawModel(ModelHandle);
		//FPS�̕\��
		fpsDisplay();
		//���f���̑���,�`��
		p->control();
		p->display();
		t.display();
		if(mShot->collisionTarget(t.getModelHandle()) > 0){
			t.delTarget();
			t.newTarget();
		}
		//�����܂�
		//����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}
	MV1DeleteModel(ModelHandle);
	delete mShot;
	delete p;
}
void MANAGIMENT :: battleModeC(){
	int ModelHandle;
	//���ǂݍ���
	ModelHandle = MV1LoadModel("model\\floor\\floor.mqo");
	MV1SetScale(ModelHandle, VGet(1.5f, 0, 1.5f));
	MV1SetPosition(ModelHandle, VGet(0, 0, 0));

	//�e�̔z��̊m��
	SHOT* mShot;
	SHOT* eShot;
	mShot = new SHOT(GetColor(255, 255, 0));
	eShot = new SHOT(GetColor(255, 0, 0));
	//���f���̓ǂݍ���
	PLAYER* p;
	ENEMY* e;
	p = new PLAYER(VGet(0, 0, 4000.0), 0.0f, mShot);
	e = new ENEMY(VGet(0, 0, -4000), PI, eShot);

	while(ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		// ��ʂ��N���A
		ClearDrawScreen();
		//��������
		//���̕`��
		MV1DrawModel(ModelHandle);
		//FPS�̕\��
		fpsDisplay();
		//���f���̑���,�`��
		//�v���C���[
		p->control();
		p->display();
		//�G
		e->control(p->getRotateY(), p->getVector());
		e->display();
		
		if(p->damageCheck(eShot) <= 0)
			break;
		if(e->damageCheck(mShot) <= 0)
			break;
		mShot->collisionModel(e->getModelHandle());
		eShot->collisionModel(p->getModelHandle());
		//�����܂�
		//����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}

	while(ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		// ��ʂ��N���A
		ClearDrawScreen();
		//���̕`��
		MV1DrawModel(ModelHandle);
		//FPS�̕\��
		fpsDisplay();
		p->addCR(0.01f);
		p->display();
		e->display();
		//����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}
		
	MV1DeleteModel(ModelHandle);
	delete mShot;
	delete eShot;
	delete p;
	delete e;
}

void MANAGIMENT :: battleModeH(){
		int ModelHandle;
	//���ǂݍ���
	ModelHandle = MV1LoadModel("model\\floor\\floor.mqo");
	MV1SetScale(ModelHandle, VGet(1.5f, 0, 1.5f));
	MV1SetPosition(ModelHandle, VGet(0, 0, 0));

	//�e�̔z��̊m��
	SHOT* mShot;
	SHOT* eShot;
	mShot = new SHOT(GetColor(255, 255, 0));
	eShot = new SHOT(GetColor(255, 0, 0));
	//���f���̓ǂݍ���
	PLAYER* p;
	ENEMY_NET* e;
	p = new PLAYER(VGet(0, 0, 4000.0), 0.0f, mShot);
	e = new ENEMY_NET(VGet(0, 0, -4000), PI, eShot);

	while(ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		// ��ʂ��N���A
		ClearDrawScreen();
		//��������
		//���̕`��
		MV1DrawModel(ModelHandle);
		//FPS�̕\��
		fpsDisplay();
		//���f���̑���,�`��
		//�v���C���[
		p->control();
		p->display();
		//�G
		e->control(/*p->getRotateY(), p->getVector()*/);
		e->display();
		
		if(p->damageCheck(eShot) <= 0)
			break;
		if(e->damageCheck(mShot) <= 0)
			break;
		mShot->collisionModel(e->getModelHandle());
		eShot->collisionModel(p->getModelHandle());
		//�����܂�
		//����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}

	while(ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		// ��ʂ��N���A
		ClearDrawScreen();
		//���̕`��
		MV1DrawModel(ModelHandle);
		//FPS�̕\��
		fpsDisplay();
		p->addCR(0.01f);
		p->display();
		e->display();
		//����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}
		
	MV1DeleteModel(ModelHandle);
	delete mShot;
	delete eShot;
	delete p;
	delete e;
}