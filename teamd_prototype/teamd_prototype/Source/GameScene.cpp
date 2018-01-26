//=====================================================================
//						  GameScene.cpp
//						ゲーム管理クラス
//=====================================================================
using namespace std;

// GameScene.h
#include "BaseScene.h"
#include "Vector2.h"		
#include "Effect.h"			
#include "EffectManager.h"	
#include "GameScene.h"		

// GameScene.cpp
#include "KeyInput.h"
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
GameScene::GameScene()
	:_playerInFrame(170,200,0,0)
{
	_groundPosY = 400.0f;
	int w, h;
	GetWindowSize(&w, &h);
	_playerInFrame.ReSize(Vector2(w - 340, h - 300));

	_minLimit = -2000;
	_maxLimit = static_cast<float>(w) + 2000;

	SoundManager::GetInstance().PlayLoop(BGM_GAME);
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
	BloodManager& bloodMng = BloodManager::Instance();
	bloodMng.Init();

	//シーン切り替えフラグ
	_isChange = false;
	_crusheCount = 0;

	_player = new Player();
	_prevPlayerGroundFlg = _player->IsGround();
	for (int i = 0; i < 50; ++i) {
		int w, h;
		GetWindowSize(&w, &h);
		Vector2 pos = { static_cast<float>(rand() % ((_maxLimit-w)*2) + _minLimit),static_cast<float>(rand() % h) };
		_nyns.push_back(new EnemyNyn(pos, *_player));
	}
	//for (int i = 0; i < 3; ++i) {
	//	float rSize = static_cast<float>((rand() % 150) + 15);
	//	_cb1List.push_back(new CB_1(Rect2(Vector2(static_cast<float>(rand() % 1000), 300.0f), Vector2(rSize, rSize))));
	//}

	
	//背景画像をロード
	backImg = LoadGraph("../image/haikei.jpg");
	
	for (int i = 0; i < 10; ++i) {
		int w, h;
		GetWindowSize(&w, &h);
		Vector2 pos = { static_cast<float>(rand() % ((_maxLimit - w) * 2) + _minLimit),static_cast<float>(rand() % h) };
		_houses.push_back(new House(pos));
	}

	//開始時間の取得
	timeCun = 0;
	timeStart = GetNowCount();

	//変更●-------------
	//score画像
	scoreImg = LoadGraph("../image/Score.png");
	timeImg = LoadGraph("../image/Time.png");
	LoadDivGraph("../image/Num.png", 10, 10, 1, 22, 36, numImg);
	coronImg = LoadGraph("../image/colon.png");
	//----------
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
	for (auto house : _houses) {
		delete house;
	}
	_houses.clear();
	for (auto e : _nyns) {
		delete e;
	}
	_nyns.clear();
}

//---------------------------------------------------------------------
//　更新
//---------------------------------------------------------------------
void GameScene::Update()
{
	EffectManager& efcMng = EffectManager::Instance();
	BloodManager& bloodMng = BloodManager::Instance();
	bool deadFlg = false;
	KeyInput& key = KeyInput::GetInstance();
	Camera& camera = Camera::Instance();
	int windowWidth, windowHeight;
	GetWindowSize(&windowWidth, &windowHeight);

	//resultへ
	if (key.GetKeyUp(KEY_INPUT_2))
	{
		SceneManager::GetInstance().ChangeScene(SType_RESULT);
		SoundManager::GetInstance().Stop(BGM_GAME);
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
		for (auto nyn : _nyns) {
			nyn->Update();
		}
		for (auto house : _houses) {
			house->Update();
		}
		bloodMng.Update();
		//for (auto cb : _cb1List) {
		//	cb->Update();
		//}
		//nynの死亡確認
		for (auto it = _nyns.begin(); it != _nyns.end();) {
			if ((*it)->GetState() == Enemy::State::isDed) {
				//SE呼び出し
				//キャラクタが持ってた方が可用性は高い、が知らん
				SoundManager::GetInstance().Play(TENKA);
				delete *it;
				it = _nyns.erase(it);
				++_crusheCount;
				SceneManager::GetInstance().SetScore(_crusheCount);//scoreのセット
				continue;
			}
			++it;
		}
		//はうすの死亡確認
		for (auto it = _houses.begin(); it != _houses.end();) {
			if ((*it)->IsDead()) {
				SoundManager::GetInstance().Play(HIT_1);
				delete *it;
				it = _houses.erase(it);
				++_crusheCount;
				SceneManager::GetInstance().SetScore(_crusheCount);//scoreのセット
				continue;
			}
			++it;
		}
		//カメラの移動
		//カメラ動かし
		{
			Rect2 playerRect = _player->Rect();
			Vector2 framePos = _playerInFrame.LT() + (camera.Pos() + camera.Offset());
			Vector2 frameSize = _playerInFrame.Size();
			//カメラのフレーム内から出てたら、そいつに合わせるように移動させる
			//→プレイヤーの矩形に合わせればいい。
			framePos.x = max(min(framePos.x, playerRect.Left()),playerRect.Right() - frameSize.x);
			framePos.y = max(min(framePos.y, playerRect.Top()), playerRect.Bottom() - frameSize.y);

			Vector2 moveValue = framePos - (_playerInFrame.LT() + (camera.Pos() + camera.Offset()));
			camera.Move(moveValue);
		}
		//同時にやるのがいけないんやな
		//そのフレームの出来事なんだし、
		//まず先に変形のみやってしまう
		//上から押されたときのみにしましょー
		//for (auto cb : _cb1List) {
		//	if (IsHit(cb->Rect(), _player->Rect())) {
		//		Rect2 ol = Overlap(cb->Rect(), _player->Rect());
		//		//Yの方向に戻るのなら、Y方向から来たってことで、つぶしちゃう
		//		if (ol.Size().x > ol.Size().y) {
		//			cb->Crushed(*_player);
		//		}
		//	}
		//}
		//houseのつぶし
		//for (auto house : _houses) {
		//	if (IsHit(house->Rect(), _player->Rect())) {
		//		Rect2 ol = Overlap(house->Rect(), _player->Rect());
		//		//Yの方向に戻るのなら、Y方向から来たってことで、つぶしちゃう
		//		if (ol.Size().x > ol.Size().y) {
		//			house->Crushed(*_player);
		//		}
		//	}
		//}
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

		//次に押し出し
		//for (auto cb : _cb1List) {
		//	Rect2 cbr = cb->Rect();
		//	//player
		//	if (IsHit(_player->Rect(), cb->Rect())) {
		//		extrusion(cbr, plr);
		//		_player->SetRect(plr);
		//		pgflg = true;
		//	}
		//	//ground
		//	if (cb->Rect().Bottom() > _groundPosY) {
		//		cbr.Move(Vector2(0.0f, _groundPosY - cb->Rect().Bottom()));
		//		cb->SetRect(cbr);
		//		cb->SetGroundFlg(true);
		//	}
		//	else {
		//		cb->SetGroundFlg(false);
		//	}
		//}
		//
		//押し出し処理をするために行ってる実装のせいで
		//訳が分からなくなってきた。
		//押し出し処理は中間にいないとだろうから、
		//それを保ちながら、見やすい処理にしてほしい。
		//houseのOnCollided
		for (auto house : _houses) {
			if (IsHit(house->Rect(), _player->Rect())) {
				house->OnCollided(*_player);
			}
		}
		//こっから↓は押し出しのみ！とかならわかりやすいかな
		Rect2 plr = _player->Rect();
		bool pgflg = false;
		//プレイヤーと地面
		if (_player->Rect().Bottom() >_groundPosY) {
			plr.Move(Vector2(0.0f, _groundPosY - _player->Rect().Bottom()));
			_player->SetRect(plr);
			pgflg = true;
		}
		//おうち
		for (auto house : _houses) {
			Rect2 hr = house->Rect();
			bool houseGroundFlg = false;
			//とplayer
			if (IsHit(_player->Rect(), house->Rect())) {
				if (!house->SideHitFlag()) {
					//横からは当たってほしくないので、汎用は使わない
					Rect2 ol = Overlap(hr, plr);
					Vector2 cbCenter = hr.Center();
					Vector2 plCenter = plr.Center();
					Vector2 moveValue = Vector2::ZERO;
					Vector2 vec = plCenter - cbCenter;
					//縦への押し出し
					moveValue.y = ol.Size().y;
					if (vec.y < 0.0f) {
						moveValue.y *= -1.0f;
					}
					//player
					plr.Move(moveValue);
					_player->SetRect(plr);
					pgflg = true;
				}
			}
			//と地面
			if (house->Rect().Bottom() > _groundPosY) {
				hr.Move(Vector2(0.0f, _groundPosY - house->Rect().Bottom()));
				house->SetRect(hr);
				houseGroundFlg = true;
			}
			house->SetGroundFlag(houseGroundFlg);
		}
		//nyn
		for (auto nyn : _nyns) {
			bool nynGroundFlg = false;
			Rect2 nynRect = nyn->Rect();
			//飛びすぎちゃうなぁ。
			if (IsHit(_player->Rect(), nyn->Rect())) {
				nyn->OnCollided(*_player);
			}
			//ground
			if (nyn->Rect().Bottom() > _groundPosY) {
				nynRect.Move(Vector2(0.0f, _groundPosY - nyn->Rect().Bottom()));
				nyn->SetRect(nynRect);
				nynGroundFlg = true;
			}
			nyn->SetGroundFlag(nynGroundFlg);
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


		TimeCunter();
	}
}
//---------------------------------------------------------------------
//　時間カウント
//---------------------------------------------------------------------
void GameScene::TimeCunter()
{
	//経過時間
	timeCun = (GetNowCount() - timeStart) * 0.001;

	//時間になったら
	if (timeCun >= TIME_MAX)
	{

	}


}
//---------------------------------------------------------------------
//　描画
//---------------------------------------------------------------------
void GameScene::Draw()
{

	//パラメタ取得やらなんやら
	EffectManager& efcMng = EffectManager::Instance();
	BloodManager& bloodMng = BloodManager::Instance();
	Camera& camera = Camera::Instance();
	Vector2 offset = camera.Pos() + camera.Offset();
	int windowW, windowH;
	GetWindowSize(&windowW, &windowH);

	DxLib::DrawGraph( 0, 0, _texID, false );	//背景
	//背景を描画するぜ
	DrawExtendGraph(0, 0,windowW,windowH,backImg, false);
	//ground描画
	Rect2 ground = {0.0f,_groundPosY,static_cast<float>(windowW),static_cast<float>(windowH) };
	Vector2 groundOffset = { 0.0f,offset.y };
	ground.Move(-groundOffset);
	DxLib::DrawBox(ground.Left(), ground.Top(), ground.Right(), ground.Bottom(), GetColor(18,198,88), true);
	//スコア等描画
	//DxLib::DrawString(10, 10, "GameScene", 0xffffffff);
	//DxLib::DrawFormatString(10, 25, 0xffffffff, "破壊数：%d", _crusheCount);

	//house
	for (auto house : _houses) {
		house->Draw(camera);
	}
	//player
	_player->Draw(offset);
	//nyn
	for (auto nyn : _nyns) {
		nyn->Draw(camera);
	}
	bloodMng.Draw(camera);
	//cb
	//for (auto cb : _cb1List) {
	//	cb->Draw(offset);
	//	Rect2 cbr = cb->Rect();
	//	cbr.Move(-offset);
	//	DxLib::DrawBox(cbr.Left(), cbr.Top(), cbr.Right(), cbr.Bottom(), 0xf0f0f0ff, false);
	//}


	//カメラフレーム範囲
	DxLib::DrawBox(_playerInFrame.Left(), _playerInFrame.Top(), _playerInFrame.Right(), _playerInFrame.Bottom(),
		0xffffffff, false);

	efcMng.Draw(offset);						//エフェクト

												//変更●-----
												//score画像
	DrawGraph(10, 10, scoreImg, true);

	DrawGraph(120, 10, numImg[(_crusheCount / 100) % 10], true);
	DrawGraph(156, 10, numImg[(_crusheCount / 10) % 10], true);
	DrawGraph(192, 10, numImg[(_crusheCount / 1) % 10], true);
	//time画像
	DrawGraph(10, 70, timeImg, true);

	int num1 = ((GetNowCount() - timeStart) % 100) / 10;
	int num2 = ((GetNowCount() - timeStart) % 1000) / 100;

	DrawGraph(120, 70, numImg[(timeCun / 10) % 10], true);
	DrawGraph(156, 70, numImg[(timeCun / 1) % 10], true);

	DrawGraph(192, 70, coronImg, true);

	DrawGraph(228, 70, numImg[(num2 / 1) % 10], true);
	DrawGraph(264, 70, numImg[(num1 / 1) % 10], true);

	//----------
										//時間描画
	//DxLib::DrawFormatString(10, 40, 0x00000000, "時間：%d:%d%d", timeCun, ((GetNowCount() - timeStart) % 1000) / 100, ((GetNowCount() - timeStart) % 100) / 10);

}