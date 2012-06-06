#include "DxLib.h"
#include "managiment.hpp"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ){
	MANAGIMENT main;
	SetAlwaysRunFlag(TRUE);
	SetDoubleStartValidFlag(TRUE);
	main.init();
	while(main.selectMode() != 3 && ProcessMessage() == 0)
		main.selectAction();

	DxLib_End();
	return 0;
}