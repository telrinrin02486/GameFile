//=====================================================================
//						  TutrialScene.cpp
//						ゲーム管理クラス
//=====================================================================
using namespace std;

// TutrialScene.h
#include "BaseScene.h"
#include "Vector2.h"			// 使用なし
#include "Effect.h"				// Vector2
#include "EffectManager.h"		// Effect、Vector2、std
#include "ImageMng.h"
#include "TutrialScene.h"		// BaseScene、EffectManager

// TutrialScene.cpp
#include "KeyInput.h"			// 使用なし
#include "DxLib.h"

#include "Camera.h"

#include "Player.h"
#include "CB_1.h"
#include "../House.h"			//なぜかこいつだけこうしないと反応しない。ん？
#include "EnemyNyn.h"

#include "Collision.h"
#include "SceneManager.h"
#include "../BloodManager.h"

#include "SoundManager.h"

//---------------------------------------------------------------------
//　コンストラクタ
//---------------------------------------------------------------------
TutrialScene::TutrialScene()
	:_playerInFrame(170, 50, 0, 0)
{
	
}

//---------------------------------------------------------------------
//　デストラクタ
//---------------------------------------------------------------------
TutrialScene::~TutrialScene()
{

}

//---------------------------------------------------------------------
//　初期化
//---------------------------------------------------------------------
void TutrialScene::Initialize()
{
	//背景画像をロード
	backImg = LoadGraph("../image/sceneBack/tutrial/tutrial.png");
	SceneManager::GetInstance().setSceneType(SType_TITLE);
}

//---------------------------------------------------------------------
//　終了処理
//---------------------------------------------------------------------
void TutrialScene::Finalize()
{
	
}

//---------------------------------------------------------------------
//　更新
//---------------------------------------------------------------------
void TutrialScene::Update()
{
	KeyInput& key = KeyInput::GetInstance();
	//まだ存在しないので
	//isScene == SType_TUTORIALの状態で
	//ENTER押さないでね
	//game
	 if (key.GetKeyUp(KEY_INPUT_RETURN))
	{
		ImageMng::GetInstance()->setUIID("../image/UI/mask/mask.png", ID_mask, { buttomPos1.x, buttomPos1.y }, { buttomPos1.x + 150,buttomPos1.y + 50 });
		SoundManager::GetInstance().Stop(BGM_TITLE);
		SoundManager::GetInstance().Play(BUTTON_2);
		SceneManager::GetInstance().ChangeScene(SceneManager::GetInstance().getSceneType());
	}
	else
	{
		//key入力なし
	}
}
//---------------------------------------------------------------------
//　時間カウント
//---------------------------------------------------------------------
void TutrialScene::TimeCunter()
{
	
}
//---------------------------------------------------------------------
//　描画
//---------------------------------------------------------------------
void TutrialScene::Draw()
{
	//背景を描画するぜ
	DrawExtendGraph(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, backImg, false);
	
}