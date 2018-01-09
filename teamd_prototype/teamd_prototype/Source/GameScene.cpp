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
#include "SceneManager.h"

//---------------------------------------------------------------------
//　コンストラクタ
//---------------------------------------------------------------------
GameScene::GameScene()
	:_ground(0,400,2000,1000)
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
	EffectManager& efMng = EffectManager::Instance();
	//シーン切り替えフラグ
	_isChange = false;
	_crusheCount = 0;

	_player = new Player();
	_prevPlayerGroundFlg = _player->IsGround();

	for (int i = 0; i < 3; ++i) {
		float rSize = static_cast<float>((rand() % 150) + 15);
		_cb1List.push_back(new CB_1(Rect2(Vector2(static_cast<float>(rand() % 1000), 300.0f), Vector2(rSize, rSize))));
	}

	
	//背景画像をロード
	backImg = LoadGraph("../image/haikei.jpg");
	
}

//---------------------------------------------------------------------
//　終了処理
//---------------------------------------------------------------------
void GameScene::Finalize()
{
	//各種開放

	delete _player;
	for (auto cb : _cb1List) {
		delete cb;
	}
	_cb1List.clear();
}

//---------------------------------------------------------------------
//　更新
//---------------------------------------------------------------------
void GameScene::Update()
{
	EffectManager& efcMng = EffectManager::Instance();
	bool deadFlg = false;
	KeyInput& key = KeyInput::GetInstance();
	Camera& camera = Camera::Instance();

	//resultへ
	if (key.GetKeyUp(KEY_INPUT_2))
	{
		SceneManager::GetInstance().ChangeScene(SType_RESULT);
	}
	else 
	{
		if (key.GetKeyUp(KEY_INPUT_1)) {
			//これ結構怖いなぁ。
			//finalize忘れてたらメモリリーク起こるじゃん
			Finalize();
			Initialize();//リセット
		}
		//　更新---------------------------------------------------------------
		_player->Update();

		for (auto cb : _cb1List) {
			cb->Update();
		}
		for (auto it = _cb1List.begin(); it != _cb1List.end();) {
			if ((*it)->IsDead()) {
				float rSize = static_cast<float>((rand() % 150) + 15);
				(*it)->Init(Rect2(Vector2(rand() % 1000, 300), Vector2(rSize, rSize)));
				++_crusheCount;
				continue;
			}
			++it;
		}
		//if (!(deadFlg = _cb->IsDead())) {
		//	_cb->Update();
		//}
		//同時にやるのがいけないんやな
		//そのフレームの出来事なんだし、
		//まず先に変形のみやってしまう
		//上から押されたときのみにしましょー
		for (auto cb : _cb1List) {
			if (IsHit(cb->Rect(), _player->Rect())) {
				Rect2 ol = Overlap(cb->Rect(), _player->Rect());
				//Yの方向に戻るのなら、Y方向から来たってことで、つぶしちゃう
				if (ol.Size().x > ol.Size().y) {
					cb->Crushed(*_player);
				}
			}
		}
		//押し出し関数
		auto extrusion = [](Rect2& r1_, Rect2& r2_) {
			//あれ？これ押し出すのどうしよう
			//これじゃ相手から一方的に押されてるんだけど。
			Rect2 ol = Overlap(r1_, r2_);
			Vector2 cbCenter = r1_.Center();
			Vector2 plCenter = r2_.Center();
			Vector2 moveValue = Vector2::ZERO;
			Vector2 vec = plCenter - cbCenter;
			//どの方向に押し出すか決めるマン。
			//結果としては外積使うのと大して変わらんのちゃう？
			if (ol.Size().x < ol.Size().y) {
				moveValue.x = ol.Size().x;
				if (vec.x < 0.0f) {
					moveValue.x *= -1.0f;
				}
			}
			else {
				moveValue.y = ol.Size().y;
				if (vec.y < 0.0f) {
					moveValue.y *= -1.0f;
				}
			}
			//とりあえず1つ目を動かす形で。
			r2_.Move(moveValue);
		};
		Rect2 plr = _player->Rect();
		Rect2 grdr = _ground;
		bool pgflg = false;

		//次に押し出し
		for (auto cb : _cb1List) {
			Rect2 cbr = cb->Rect();
			//player
			if (IsHit(_player->Rect(), cb->Rect())) {
				extrusion(cbr, plr);
				_player->SetRect(plr);
				pgflg = true;
			}
			//ground
			if (IsHit(cb->Rect(), _ground)) {
				extrusion(grdr, cbr);
				cb->SetRect(cbr);
				cb->SetGroundFlg(true);
			}
			else {
				cb->SetGroundFlg(false);
			}
		}
		//
		if (IsHit(_player->Rect(), _ground)) {
			extrusion(grdr, plr);
			_player->SetRect(plr);
			pgflg = true;
		}
		_player->SetGroundFlg(pgflg);
		//プレイヤーが地面に降り立った瞬間揺れを設定
		if (!_prevPlayerGroundFlg && _player->IsGround()) {
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
void GameScene::Draw()
{
	//背景を描画するぜ
	DrawGraph(0, 0, backImg, false);

	EffectManager& efcMng = EffectManager::Instance();
	Camera& camera = Camera::Instance();
	Vector2 offset = camera.Pos() + camera.Offset();
	DxLib::DrawGraph( 0, 0, _texID, false );	//背景
	Rect2 ground = _ground;
	ground.Move(offset);
	DrawBox(ground.Left(), ground.Top(), ground.Right(), ground.Bottom(), 0xff0fff0f, true);

	DrawString(10, 10, "GameScene", 0xffffffff);
	DrawFormatString(10, 25, 0xffffffff, "破壊数：%d", _crusheCount);
	_player->Draw(offset);
	for (auto cb : _cb1List) {
		cb->Draw(offset);
		const Rect2 cbr = cb->Rect();
		DrawBox(cbr.Left(), cbr.Top(), cbr.Right(), cbr.Bottom(), 0xf0f0f0ff, false);
	}
	//if (!(_cb == nullptr)) {
	//	_cb->Draw(offset);
	//}
	efcMng.Draw();						//エフェクト


	
}