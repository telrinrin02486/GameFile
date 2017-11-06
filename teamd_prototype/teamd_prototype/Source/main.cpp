
#include <iostream>

#include <DxLib.h>

#include "CB_1.h"

//
#include "EffectManager.h"
#include "Camera.h"

#include "Rect2.h"

#include "Player.h"

#include "Input.h"

using namespace DxLib;
using namespace std;

constexpr unsigned int WINDOW_WIDTH = 640;
constexpr unsigned int WINDOW_HEIGHT = 480;




/////////////////
int main(int argc, char *argv[]) {

	max(1, 2);

	int err = 0;
	err = ChangeWindowMode(TRUE);
	err = DxLib_Init();
	err = SetMainWindowText("TeamDestory_Prototype");
	err = SetDrawScreen(DX_SCREEN_BACK);
	err = SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);




	Camera& camera = Camera::Instance();

	Rect2 r1, r2;
	r1 = Rect2(Vector2(20, 20), Vector2(20, 20));
	r2 = Rect2(Vector2(30, 50), Vector2(20, 20));
	Player player(r1);
	CB_1 cb(r2);

	Input& input = Input::GetInstance();
	input.Initialize();



	while (	!ProcessMessage() && !ScreenFlip() && !ClearDrawScreen() &&
		CheckHitKey(KEY_INPUT_ESCAPE) == 0) {

		input.Update();
		player.Update();
		camera.Update();

		Vector2 cameraPos = camera.Pos() + camera.Offset();



		//つぶし
		//まずつぶす
		//潰した後の矩形もらう
		//座標を合わせる。（




		player.Rect().Draw(cameraPos, 0xff0000ff);
		r2.Draw(cameraPos, 0xff00ff00);



		if (input.GetKey(KEY_INPUT_1)) {
			camera.SetEarthquake(Vector2(10.0f, 0.0f));
		}

		


		

	}
	err = DxLib_End();
	return 0;
}