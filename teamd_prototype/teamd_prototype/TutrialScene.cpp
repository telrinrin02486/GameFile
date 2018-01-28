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
#include "TutrialScene.h"			// BaseScene、EffectManager

// TutrialScene.cpp
#include "KeyInput.h"		// 使用なし
#include "DxLib.h"

#include "Camera.h"

#include "Player.h"
#include "CB_1.h"
#include "../House.h"//なぜかこいつだけこうしないと反応しない。ん？
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
	_groundPosY = 400.0f;
	int w, h;
	GetWindowSize(&w, &h);
	_playerInFrame.ReSize(Vector2(w - 340, (h / 3) * 2));

	_minLimit = -2000;
	_maxLimit = static_cast<float>(w) + 2000;

	SoundManager::GetInstance().PlayLoop(BGM_TUTRIAL);
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
	EffectManager& efMng = EffectManager::Instance();
	BloodManager& bloodMng = BloodManager::Instance();
	bloodMng.Init();
	//背景画像をロード
	backImg = LoadGraph("../image/haikei.jpg");

	_player = new Player(Vector2(0.0f, 50.0f));
	_player->SetPos({ WINDOW_WIDTH  / 2, WINDOW_HEIGHT  / 2});//tutrialなのでstartPosの再設定
	_prevPlayerGroundFlg = _player->IsGround();
	
	int w, h;
	GetWindowSize(&w, &h);
	Vector2 pos = { _player->Pos().x, _player->Pos().y };
	enemy = new EnemyNyn(pos, *_player);
	
}

//---------------------------------------------------------------------
//　終了処理
//---------------------------------------------------------------------
void TutrialScene::Finalize()
{
	//各種開放

	delete _player;

	delete enemy;
}

//---------------------------------------------------------------------
//　更新
//---------------------------------------------------------------------
void TutrialScene::Update()
{
	EffectManager& efcMng = EffectManager::Instance();
	BloodManager& bloodMng = BloodManager::Instance();
	bool deadFlg = false;
	KeyInput& key = KeyInput::GetInstance();
	Camera& camera = Camera::Instance();
	int windowWidth, windowHeight;
	GetWindowSize(&windowWidth, &windowHeight);

	//resultへ
	if (key.GetKeyUp(KEY_INPUT_RETURN))
	{
		SceneManager::GetInstance().ChangeScene(SType_TITLE);
		SoundManager::GetInstance().Stop(BGM_TUTRIAL);
	}
	else
	{
		//破壊対象オブジェクトのリセット
		if (key.GetKeyUp(KEY_INPUT_1)) 
		{
			//これ結構怖いなぁ。
			//finalize忘れてたらメモリリーク起こるじゃん
			Finalize();
			Initialize();//リセット
		}
		//　更新---------------------------------------------------------------
		_player->Update(true);
		if (enemy != nullptr)
		{
			enemy->Update();
		}
		bloodMng.Update();
		
		
		if (enemy != nullptr)
		{
			if (enemy->GetState() == Enemy::State::isDed)
			{
				//SE呼び出し
				//キャラクタが持ってた方が可用性は高い、が知らん
				SoundManager::GetInstance().Play(TENKA);
				delete enemy;
				enemy = nullptr;
			}
		}
		
		
		//カメラの移動
		//カメラ動かし
		{
			Rect2 playerRect = _player->Rect();
			Vector2 framePos = _playerInFrame.LT() + (camera.Pos() + camera.Offset());
			Vector2 frameSize = _playerInFrame.Size();
			//カメラのフレーム内から出てたら、そいつに合わせるように移動させる
			//→プレイヤーの矩形に合わせればいい。
			framePos.x = max(min(framePos.x, playerRect.Left()), playerRect.Right() - frameSize.x);
			framePos.y = max(min(framePos.y, playerRect.Top()), playerRect.Bottom() - frameSize.y);

			Vector2 moveValue = framePos - (_playerInFrame.LT() + (camera.Pos() + camera.Offset()));
			camera.Move(moveValue);
		}
		
		

		
		//こっから↓は押し出しのみ！とかならわかりやすいかな
		Rect2 plr = _player->Rect();
		bool pgflg = false;

		//プレイヤーと地面
		if (_player->Rect().Bottom() >_groundPosY) 
		{
			plr.Move(Vector2(0.0f, _groundPosY - _player->Rect().Bottom()));
			_player->SetRect(plr);
			pgflg = true;
		}
		
		//enemy
		if (enemy != nullptr)
		{
			bool nynGroundFlg = false;
			Rect2 nynRect = enemy->Rect();
			//飛びすぎちゃうなぁ。
			if (IsHit(_player->Rect(), enemy->Rect()))
			{
				enemy->OnCollided(*_player);
			}
			//ground
			if (enemy->Rect().Bottom() > _groundPosY)
			{
				nynRect.Move(Vector2(0.0f, _groundPosY - enemy->Rect().Bottom()));
				enemy->SetRect(nynRect);
				nynGroundFlg = true;
			}
			enemy->SetGroundFlag(nynGroundFlg);
		}
		
		_player->SetGroundFlg(pgflg);
		//プレイヤーが地面に降り立った瞬間揺れを設定
		if (!_prevPlayerGroundFlg && _player->IsGround()) 
		{
			camera.SetEarthquake(Vector2(0.0f, 5.0f));
		}
		_prevPlayerGroundFlg = _player->IsGround();

		efcMng.Update();
		camera.Update();

		//	消滅処理-----------------------------------------------------------
		efcMng.Delete();

	}
}

//---------------------------------------------------------------------
//　描画
//---------------------------------------------------------------------
void TutrialScene::Draw()
{

	//パラメタ取得やらなんやら
	EffectManager& efcMng = EffectManager::Instance();
	BloodManager& bloodMng = BloodManager::Instance();
	Camera& camera = Camera::Instance();
	Vector2 offset = camera.Pos() + camera.Offset();
	int windowW, windowH;
	GetWindowSize(&windowW, &windowH);

	//背景を描画するぜ										
	DrawExtendGraph(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, backImg, false);

	//ground描画
	Rect2 ground = { 0.0f,_groundPosY,static_cast<float>(windowW),static_cast<float>(windowH) };
	Vector2 groundOffset = { 0.0f,offset.y };
	ground.Move(-groundOffset);
	DxLib::DrawBox(ground.Left(), ground.Top(), ground.Right(), ground.Bottom(), 0xff0fff0f, true);
	
	//player
	_player->Draw(offset);

	//enemy
	//////////
	if (enemy != nullptr)
	{
		enemy->Draw(camera);
	}
	//血
	bloodMng.Draw(camera);
	
	//エフェクト
	efcMng.Draw(offset);						

	
}