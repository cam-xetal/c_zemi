#include "enemy.hpp"

void ENEMY :: ai(){
	if(count < 10)
		return;
	float rand = getRand();
	//前後設定
	if(fFlag){
		if(rand < 0.9)
			fFlag = true;
		else
			fFlag = false;
	}else{
		if(rand < 0.9)
			fFlag = true;
		else
			fFlag = false;
	}

	//上下設定
	if(upFlag){
		if(rand < 0.6)
			upFlag = true;
		else
			upFlag = false;
	}else{
		if(rand < 0.6)
			upFlag = true;
		else
			upFlag = false;
	}

	//左右設定
	if(rRFlag == lRFlag){
		if(rand < 0.4){
			rRFlag = lRFlag;
		}else if(rand >= 0.4 && rand < 0.7){
			rRFlag = true;
			lRFlag = false;
		}else{
			rRFlag = false;
			lRFlag = true;
		}
	}else if(rRFlag){
		if(rand < 0.6){
			rRFlag = true;
			lRFlag = false;
		}else if(rand >= 0.6 && rand < 0.9){
			rRFlag = false;
			lRFlag = true;
		}else{
			rRFlag = false;
			lRFlag = false;
		}
	}else{
		if(rand < 0.6){
			rRFlag = false;
			lRFlag = true;
		}else if(rand >= 0.6 && rand < 0.9){
			rRFlag = true;
			lRFlag = false;
		}else{
			rRFlag = false;
			lRFlag = false;
		}
	}
	//速度設定
	if(vFlag){
		if(rand < 0.8)
			vFlag = true;
		else
			vFlag =false;
	}else{
		if(rand < 0.9)
			vFlag = true;
		else
			vFlag = false;
	}
}

void ENEMY :: ai(VECTOR pV){
	VECTOR eV = getVector();
	pV.y = 0.0f;
	eV.y = 0.0f;
	float sin = VSize(VCross(pV, eV))/(VSize(pV)*VSize(eV));
	sin *=0.7f;
	DrawFormatString(20, 60, GetColor(255, 255, 255), "%f", sin);
		if(count < 10)
		return;
	float rand = getRand();
	//前後設定
	if(fFlag){
		if(rand < 0.9)
			fFlag = true;
		else
			fFlag = false;
	}else{
		if(rand < 0.9)
			fFlag = true;
		else
			fFlag = false;
	}
		//上下設定
	if(upFlag){
		if(rand < 0.6)
			upFlag = true;
		else
			upFlag = false;
	}else{
		if(rand < 0.6)
			upFlag = true;
		else
			upFlag = false;
	}

	//左右設定
	if(rRFlag == lRFlag){
		if(rand < 0.2){
			rRFlag = lRFlag;
		}else if(rand >= 0.2 && rand < 0.2 + 1-sin){
			rRFlag = true;
			lRFlag = false;
		}else{
			rRFlag = false;
			lRFlag = true;
		}
	}else if(rRFlag){
		if(rand < sin){
			rRFlag = true;
			lRFlag = false;
		}else if(rand >= sin && rand < 0.2 + sin){
			rRFlag = false;
			lRFlag = true;
		}else{
			rRFlag = false;
			lRFlag = false;
		}
	}else{
		if(rand < 1-sin){
			rRFlag = false;
			lRFlag = true;
		}else if(rand >= 1 - sin && rand < 0.2 + 1.0 - sin){
			rRFlag = true;
			lRFlag = false;
		}else{
			rRFlag = false;
			lRFlag = false;
		}
	}
	//速度設定
	if(vFlag){
		if(rand < 0.8)
			vFlag = true;
		else
			vFlag =false;
	}else{
		if(rand < 0.9)
			vFlag = true;
		else
			vFlag = false;
	}
}

void ENEMY :: ai(float rotateY, VECTOR pV){
	VECTOR eV = getVector();
	float cos = VDot(pV, eV)/(VSize(pV)*VSize(eV));
	
	if(count < 10)
		return;
	float rand = getRand();
	//前後設定
	fFlag = true;
	bFlag = false;
	/*
	if(fFlag == bFlag){
		if(rand < 0.9){
			fFlag = true;
			bFlag = false;
		}else if(rand >= 0.9 && rand < 0.95){
			fFlag = false;
			bFlag = true;
		}else{
			fFlag = false;
			bFlag = false;
		}
	}else if(fFlag){
		if(rand < 0.9){
			fFlag = true;
			bFlag = false;
		}else if(rand >= 0.9 && rand < 0.96){
			fFlag = false;
			bFlag = false;
		}else{
			fFlag = false;
			bFlag = true;
		}
	}else{
		if(rand < 0.8){
			fFlag = true;
			bFlag = false;
		}else if(rand >= 0.8 && rand < 0.95){
			fFlag = false;
			bFlag = false;
		}else{
			fFlag = false;
			bFlag = true;
		}
	}*/
	//上下設定
	if(pV.y >= this->y){
		if(rand < 0.95)
			upFlag = true;
		else
			upFlag = false;
	}else{
		if(rand < 0.95)
			upFlag = false;
		else
			upFlag = true;
	}
	
	//左右設定
	float tmp = rotateY - this->rotateY;
	if(fabs(cos) > 0.95){
		if(rand < 0.5){
			rRFlag = false;
			lRFlag = false;
		}else if(rand >= 0.5 && rand < 0.75){
			rRFlag = true;
			lRFlag = false;
		}else{
			rRFlag = false;
			lRFlag = true;
		}
	}else if(fabs(tmp) < 0.05){
		if(rand < 0.6){
			rRFlag = true;
			lRFlag = false;
		}else if(rand >= 0.6 && rand < 0.8){
			rRFlag = false;
			lRFlag = false;
		}else{
			rRFlag = false;
			lRFlag = true;
		}
	}else{
		rRFlag = true;
		lRFlag = false;
	}
	/*else if(fabs(tmp - 0.03) < fabs(tmp)){
		rRFlag = true;
		lRFlag = false;
	}else if(fabs(tmp + 0.03) < fabs(tmp)){
		rRFlag = false;
		lRFlag = true;
	}else{
		rRFlag = false;
		lRFlag = false;
	}*/
	
	//速度設定
	vFlag = true;
	/*
	if(vFlag){
		if(rand < 0.8)
			vFlag = true;
		else
			vFlag =false;
	}else{
		if(rand < 0.9)
			vFlag = true;
		else
			vFlag = false;
	}*/
}