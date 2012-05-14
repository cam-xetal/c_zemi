#include "DxLib.h"
#include "managiment.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ){
	MANAGIMENT main;

	main.init();
	while(main.selectMode() != 3 && ProcessMessage() == 0)
		main.selectAction();

	DxLib_End();
	return 0;
}