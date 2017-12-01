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
		
		//	ゲームの制御・更新-------------------------------------------------
		KeyInput::GetInstance().Update();		//　キー入力の更新
		SceneManager::GetInstance().Update();	//シーンの更新
		Camera::Instance().Update();			//カメラ


		//	ゲームの描画　-----------------------------------------------------
		ClearDrawScreen();					//画面の初期化
		SceneManager::GetInstance().Draw();	//シーンの描画
		ScreenFlip();						//画面の更新
	}

	//DxLibの終了処理
	DxLib::DxLib_End();

	return 0;
}