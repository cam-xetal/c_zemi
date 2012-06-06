#include "model.hpp"

void MODEL :: display(){
	playTime += 200.0f;
	if(playTime >= animTime)
		playTime = 0.0f;
	mS->move();
	mS->display();
	//MV1SetPosition(ModelHandle, VGet(x+x0, y+y0, z+z0));
	//MV1SetRotationXYZ(ModelHandle, VGet(rotateX, rotateY, rotateZ));
	MV1RefreshCollInfo(ModelHandle, 39);
	MATRIX rot = MMult(MMult(MGetRotX(rotateX), MGetRotZ(rotateZ)),MGetRotY(rotateY));
	MATRIX trans = MGetTranslate(VGet(x+x0, y+y0, z+z0));
	MV1SetMatrix(ModelHandle, MMult(rot, trans));
	MV1SetAttachAnimTime(ModelHandle, attachIndex, playTime);
	MV1DrawModel(ModelHandle);
}

void MODEL :: move(bool fFlag, bool bFlag, bool upFlag, bool rRFlag, bool lRFlag, bool vFlag){
	preX = x;
	preY = y;
	preZ = z;
	rotateX = 0.0f;
	rotateZ = 0.0f;

	//速度制御
	if(vFlag){
		v+=0.05f;
		if(v > 3.0)
			v=3.0;
	}else{
		v-= 0.01f;
		if(v < 1.0)
			v=1.0f;
	}

	//左右回転
	if(lRFlag){	//左回転
		rotateY += 0.005f*v;
		if(rotateY > 2*PI)
			rotateY -= 2*PI;
		rotateZ += PI/18.0f;
	}
	if(rRFlag){	//右回転
		rotateY -=0.005f*v;
		if(rotateY < 0)
			rotateY += 2*PI;
		rotateZ -= PI/18.0f;
	}

	
	//前後移動
	if(fFlag){	//前移動
		x -= v*10.0f * sinf(rotateY);
		if(x > MAX_X)
			x=MAX_X;
		else if(x < MIN_X)
			x=MIN_X;
		z -= v*10.0f * cosf(rotateY);
		if(z > MAX_Z)
			z=MAX_Z;
		else if(z < MIN_Z)
			z=MIN_X;
		rotateX -= PI/18.0f;
	}
	if(bFlag){	//後ろ移動
		x += v*7.5f * sinf(rotateY);
		if(x > MAX_X)
			x=MAX_X;
		else if(x < MIN_X)
			x=MIN_X;
		z += v*7.5f * cosf(rotateY);
		if(z > MAX_Z)
			z=MAX_Z;
		else if(z < MIN_Z)
			z=MIN_X;
		rotateX += PI/18.0f;
	}

	//上昇
	if(upFlag){
		y+=10.0f;
		if(y > 600.0)
			y=600.0f;
	}else{
		y-=5.0f;
		if(y < 0)
			y=0.0f;
	}
}

int MODEL :: shot(){
	//弾の発射
	if(count > 10){
		mS->newShots(	VGet(x+125*cos(PI-rotateY), y+250.0f, z+125*sin(PI-rotateY)),
						VGet(x-125*cos(PI-rotateY), y+250.0f, z-125*sin(PI-rotateY)),
						15,
						rotateY-0.005f,
						rotateY+0.005f,
						85.0f);
		/*
		mS->newShot(VGet(x+125*cos(PI-rotateY), y+250.0f, z+125*sin(PI-rotateY)), 15, rotateY-0.025f, 100.0f);
		mS->newShot(VGet(x-125*cos(PI-rotateY), y+250.0f, z-125*sin(PI-rotateY)), 15, rotateY+0.025f, 100.0f);
		*/
		count=0;
		return 1;
	}
	count++;
	return 0;
}