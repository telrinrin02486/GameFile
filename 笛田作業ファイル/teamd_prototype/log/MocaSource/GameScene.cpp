//=====================================================================
//						  GameScene.cpp
//						ゲーム管理クラス
//=====================================================================
using namespace std;

// GameScene.h
#include "BaseScene.h"
#include "Vector2.h"			// 使用なし
#include "Effect.h"				// Vector2
#include "EffectManager.h"		// Effect、Vector2、std
#include "GameScene.h"			// BaseScene、EffectManager

// GameScene.cpp
#include "KeyInput.h"		// 使用なし
#include "DxLib.h"

#include "Camera.h"

#include "Player.h"
#include "CB_1.h"

#include "Collision.h"

//---------------------------------------------------------------------
//　コンストラクタ
//---------------------------------------------------------------------
GameScene::GameScene()
{

}

//---------------------------------------------------------------------
//　デストラクタ
//---------------------------------------------------------------------
GameScene::~GameScene()
{

}

//---------------------------------------------------------------------
//　初期化
//---------------------------------------------------------------------
void GameScene::Initialize()
{
	//シーン切り替えフラグ
	_isChange = false;

	//エフェクト管理
	_effectManager = new EffectManager();

	_player = new Player();


	_cb = new CB_1(*_effectManager);


}

//---------------------------------------------------------------------
//　終了処理
//---------------------------------------------------------------------
void GameScene::Finalize()
{
	//各種開放
	//エフェクト管理
	delete _effectManager;
	delete _player;
	delete _cb;

}

//---------------------------------------------------------------------
//　更新
//---------------------------------------------------------------------
void GameScene::Update()
{
	bool deadFlg = false;
	KeyInput& key = KeyInput::GetInstance();
	Camera& camera = Camera::Instance();
	if (key.GetKeyUp(KEY_INPUT_1)) {
		Finalize();
		Initialize();//リセット
	}
	//　更新---------------------------------------------------------------
	_player->Update();
	
	if (!(deadFlg = _cb->IsDead())) {
		_cb->Update();
	}

	//当たるところさん
	//当たった後でオブジェクトの変更が行われるので
	//本実装ではダブルバッファが想定される。
	if (!deadFlg) {
		if (IsHit(_cb->Rect(), _player->Rect())) {
			_cb->Crushed(*_player);
			//オブジェクト変形後の処理
			Rect2 ol = Overlap(_cb->Rect(), _player->Rect());
			Vector2 nrmPlayerVec = _player->Vec().Normalize();
			if (IsHit(_cb->Rect(), _player->Rect())) {
				//逆ベく
				nrmPlayerVec = -nrmPlayerVec;
			}
			Vector2 moveValue = nrmPlayerVec * ol.size.Absolute();
			_player->SetPos(_player->Rect().pos + moveValue);

		}
		
	}
	_effectManager	->Update();

	//	消滅処理-----------------------------------------------------------
	_effectManager	->Delete();
}

//---------------------------------------------------------------------
//　描画
//---------------------------------------------------------------------
void GameScene::Draw()
{
	Camera& camera = Camera::Instance();
	Vector2 offset = camera.Pos() + camera.Offset();
	DxLib::DrawGraph( 0, 0, _texID, false );	//背景

	_player->Draw(offset);
	if (!(_cb == nullptr)) {
		_cb->Draw(offset);
	}
	_effectManager->Draw();						//エフェクト
}