
#include <iostream>
#include <DxLib.h>

#include "GameMain.h"


using namespace DxLib;
using namespace std;

constexpr unsigned int WINDOW_WIDTH = 640;
constexpr unsigned int WINDOW_HEIGHT = 480;

int main(int argc, char *argv[]) {

	int err = 0;
	err = ChangeWindowMode(TRUE);
	err = DxLib_Init();
	err = SetMainWindowText("TeamDestory_Prototype");
	err = SetDrawScreen(DX_SCREEN_BACK);
	err = SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);

	while (	!ProcessMessage() && !ScreenFlip() && !ClearDrawScreen() &&
		CheckHitKey(KEY_INPUT_ESCAPE) == 0) {

	}

	err = DxLib_End();
	return 0;
}