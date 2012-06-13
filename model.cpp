#include "model.hpp"

void MODEL :: display(){
	DrawCapsule3D(	VGet(x+600*sinf(rotateY), y+y0+200.0f-500*sinf(rotateX), z+600*cosf(rotateY)),
					VGet(x-200*sinf(rotateY), y+y0+200.0f+500*sinf(rotateX), z-200*cosf(rotateY)),
					210.0f, 2, GetColor(255,255,255), GetColor(255,255,255), FALSE);
	playTime += 200.0f;
	if(playTime >= animTime)
		playTime = 0.0f;
	mS->move();
	mS->display();
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
	preRX = rotateX;
	preRY = rotateY;
	preRZ = rotateZ;
	rotateX = 0.0f;
	rotateZ = 0.0f;

	//‘¬“x§Œä
	if(vFlag){
		v+=0.05f;
		if(v > 3.0)
			v=3.0;
	}else{
		v-= 0.01f;
		if(v < 1.0)
			v=1.0f;
	}

	//¶‰E‰ñ“]
	if(lRFlag){	//¶‰ñ“]
		rotateY += 0.005f*v;
		if(rotateY > 2*PI)
			rotateY -= 2*PI;
		rotateZ += PI/18.0f;
	}
	if(rRFlag){	//‰E‰ñ“]
		rotateY -=0.005f*v;
		if(rotateY < 0)
			rotateY += 2*PI;
		rotateZ -= PI/18.0f;
	}

	
	//‘OŒãˆÚ“®
	if(fFlag){	//‘OˆÚ“®
		x -= v*10.0f * sinf(rotateY);
		if(x > MAX_X)
			x = MAX_X;
		else if(x < MIN_X)
			x = MIN_X;
		z -= v*10.0f * cosf(rotateY);
		if(z > MAX_Z)
			z = MAX_Z;
		else if(z < MIN_Z)
			z = MIN_X;
		rotateX -= PI/18.0f;
	}
	if(bFlag){	//Œã‚ëˆÚ“®
		x += v*7.5f * sinf(rotateY);
		if(x > MAX_X)
			x = MAX_X;
		else if(x < MIN_X)
			x = MIN_X;
		z += v*7.5f * cosf(rotateY);
		if(z > MAX_Z)
			z = MAX_Z;
		else if(z < MIN_Z)
			z=MIN_X;
		rotateX += PI/18.0f;
	}

	//ã¸
	if(upFlag){
		y+=10.0f;
		if(y > MAX_Y)
			y=MAX_Y;
	}else{
		y-=5.0f;
		if(y < MIN_Y)
			y=MIN_Y;
	}
}

int MODEL :: shot(){
	//’e‚Ì”­ŽË
	if(count > 10){
		mS->newShots(	VGet(x+125*cos(PI-rotateY), y+250.0f, z+125*sin(PI-rotateY)),
						VGet(x-125*cos(PI-rotateY), y+250.0f, z-125*sin(PI-rotateY)),
						//15,
						VGet(rotateX, rotateY-0.0025f, rotateZ),
						VGet(rotateX, rotateY+0.0025f, rotateZ));
						//85.0f);
		count=0;
		return 1;
	}
	count++;
	return 0;
}