//===================================================================
//
//								main.cpp
//				エントリーポイントとライブラリの初期化
//
//===================================================================
using namespace std;

// main.cpp
#include "BaseScene.h"
#include "SceneManager.h"		// BaseScene
#include "SoundManager.h"

#include "Vector2.h"			// 使用なし
#include "ImageMng.h"			// std, Vector2

#include "KeyInput.h"
#include "Camera.h"
#include "DxLib.h"

#include "Const.h"


int main(void)
{
	//ウィンドウモードで起動
	ChangeWindowMode( true );
	SetTransColor( 255, 0, 255 );
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16);

	//DxLibの初期化
	if ( DxLib::DxLib_Init() == -1 )
	{
		return -1;
	}

	//ゲームの初期化
	ImageMng::GetInstance()->Create();
	SceneManager::GetInstance().Initialize();
	SoundManager::GetInstance().Initialize();

	Camera::Instance();

	while ( ProcessMessage() == 0 && CheckHitKey( KEY_INPUT_ESCAPE ) == 0 )
	{
		//　キー入力の更新-----------------------------------------------------
		KeyInput::GetInstance().Update();

		//	ゲームの制御・更新-------------------------------------------------
		SceneManager::GetInstance().Update();

		//カメラ
		Camera::Instance().Update();
		//	ゲームの描画　-----------------------------------------------------
		//画面の初期化
		ClearDrawScreen();
		
		//シーンの描画
		SceneManager::GetInstance().Draw();

		//画面の更新
		ScreenFlip();
	}

	//DxLibの終了処理
	DxLib::DxLib_End();

	return 0;
}