
#include <Windows.h>
#include <DxLib.h>
#include "GameMain.h"


#include "SceneManager.h"
#include "KeyInput.h"
#include "SoundManager.h"
#include "ImageMng.h"
#include "EffectManager.h"

int main(void){
	/*constexpr unsigned int WINDOW_WIDTH = 1080;
	constexpr unsigned int WINDOW_HEIGHT = 620;*/
	constexpr char* const WINDOW_TITLE = "TeamDestroy_β";
	int err = 0;
	err = ChangeWindowMode(TRUE);
	err = DxLib_Init();
	err = SetMainWindowText(WINDOW_TITLE);
	err = SetDrawScreen(DX_SCREEN_BACK);
	err = SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);

	GameMain& gm = GameMain::Instance();
	err = gm.Init();
	//ImageMng::Create();
	//EffectManager::Instance().Initialize();
	//SoundManager::GetInstance().Initialize();
	//SceneManager::GetInstance().Initialize();

	//ちょっと進んだ
	//SoundManager→SceneManager→SoundManagerの順で初期化してやらないと
	//音楽消える

	//ちょっとわかった
	//問題点は、SoundManagerのPlayは呼ぶたびに音楽の最初に戻すのに
	//TitleSceneのUpdateで呼び続けたこと。
	//音が止まらなくなってたのは、
	//読み込んだ音のハンドルを渡した後に初期化したから
	//ハンドルが変わって操作不能になってたから。
	
	//対策として、
	//モカ茶がやっていたみたいに、ハンドルのポインタを渡す。
	//変更が起こった場合でも対応可能。

	while (!ProcessMessage()) {
		err = gm.Update();
		ClearDrawScreen();
		err = gm.Draw();
		ScreenFlip();

		if (err == -1) {
			break;
		}
		
	}

	gm.End();
	err = DxLib_End();

	return 0;
}


//
//
//int main(int argc, char *argv[]) {
//
//	max(1, 2);
//
//	int err = 0;
//	err = ChangeWindowMode(TRUE);
//	err = DxLib_Init();
//	err = SetMainWindowText("TeamDestory_Prototype");
//	err = SetDrawScreen(DX_SCREEN_BACK);
//	err = SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);
//
//
//
//
//	Camera& camera = Camera::Instance();
//
//	Rect2 r1, r2;
//	r1 = Rect2(Vector2(20, 20), Vector2(20, 20));
//	r2 = Rect2(Vector2(30, 50), Vector2(20, 20));
//	Player player(r1);
//	CB_1 cb(r2);
//
//	Input& input = Input::GetInstance();
//	input.Initialize();
//
//
//
//	while (	!ProcessMessage() && !ScreenFlip() && !ClearDrawScreen() &&
//		CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
//
//		input.Update();
//		player.Update();
//		camera.Update();
//
//		Vector2 cameraPos = camera.Pos() + camera.Offset();
//
//
//
//		//つぶし
//		//まずつぶす
//		//潰した後の矩形もらう
//		//座標を合わせる。（
//
//
//
//
//		player.Rect().Draw(cameraPos, 0xff0000ff);
//		r2.Draw(cameraPos, 0xff00ff00);
//
//
//
//		if (input.GetKey(KEY_INPUT_1)) {
//			camera.SetEarthquake(Vector2(10.0f, 0.0f));
//		}
//
//		
//
//
//		
//
//	}
//	err = DxLib_End();
//	return 0;
//}