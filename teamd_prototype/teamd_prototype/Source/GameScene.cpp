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
#include "../GabyoMan.h"

#include "Collision.h"
#include "SceneManager.h"
#include "../BloodManager.h"

#include "SoundManager.h"
//#include "../EnemyFactory.h"/*EnemyFactorのソースが存在しないので一時コメント*/

constexpr unsigned int ENEMY_MAX = 50;
//---------------------------------------------------------------------
//　コンストラクタ
//---------------------------------------------------------------------
GameScene::GameScene()
	:_playerInFrame(170,-150,0,0)
{
	_groundPosY = 500.0f;
	int w, h;
	GetWindowSize(&w, &h);
	_playerInFrame.ReSize(Vector2(w - 340, h + 100));

	_minLimit = -2000;
	_maxLimit = static_cast<float>(w) + 2000;

	SoundManager::GetInstance().PlayLoop(BGM_GAME);

	_endTime = 60;//終了後の余韻(フレーム単位


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
	GameScene();
	EffectManager& efMng = EffectManager::Instance();
	BloodManager& bloodMng = BloodManager::Instance();
	bloodMng.Init();
	int windowWidth, windowHight;
	GetWindowSize(&windowWidth, &windowHight);
	_barrenRange = { _minLimit-100,_minLimit+500 };//不毛地帯の横幅
	//シーン切り替えフラグ
	_isChange = false;
	_crusheCount = 0;
	//初期生成
	_playerStartPos = Vector2(_minLimit, 50.0f);
	_player = new Player(_playerStartPos);
	_prevPlayerGroundFlg = _player->IsGround();
	//e
	for (int i = 0; i < 30; ++i) {
		int w, h;
		GetWindowSize(&w, &h);
		float posX = static_cast<float>(rand() % ((_maxLimit - w) * 2) + _minLimit);
		//生成禁止区域なら、なかったことにしちゃお！
		if (posX > _barrenRange.x && posX < _barrenRange.y) {
			//--i;
			continue;
		}
		Vector2 pos = {posX,_groundPosY };
		_enemis.push_back(new EnemyNyn(pos, *_player));

	}
	//gabyo
	for (int i = 0; i < 10; ++i) {
		int w, h;
		GetWindowSize(&w, &h);
		float posX = static_cast<float>(rand() % ((_maxLimit - w) * 2) + _minLimit);
		//生成禁止区域なら、なかったことにしちゃお！
		if (posX > _barrenRange.x && posX < _barrenRange.y) {
			--i;
			continue;
		}
		Vector2 pos = { posX,_groundPosY };
		_enemis.push_back(new GabyoMan(pos, *_player));

	}
	//for (int i = 0; i < 3; ++i) {
	//	float rSize = static_cast<float>((rand() % 150) + 15);
	//	_cb1List.push_back(new CB_1(Rect2(Vector2(static_cast<float>(rand() % 1000), 300.0f), Vector2(rSize, rSize))));
	//}

	
	//背景画像をロード
	backImg = LoadGraph("../image/haikei.jpg");
	//house
	for (int i = 0; i < 10; ++i) {
		int w, h;
		GetWindowSize(&w, &h);
		float posX = static_cast<float>(rand() % ((_maxLimit - w) * 2) + _minLimit);
		//生成禁止区域なら、なかったことにしちゃお！
		if (posX > _barrenRange.x && posX < _barrenRange.y) {
			--i;
			continue;
		}
		Vector2 pos = { posX,_groundPosY };
		_houses.push_back(new House(pos));
	}

	//開始時間の取得
	timeCun = TIME_MAX;
	timeStart = GetNowCount();

	//変更●-------------
	//score画像
	scoreImg = LoadGraph("../image/Score.png");
	timeImg = LoadGraph("../image/Time.png");
	LoadDivGraph("../image/Num.png", 10, 10, 1, 22, 36, numImg);
	coronImg = LoadGraph("../image/colon.png");
	LoadDivGraph("../image/count/cuntNum.png", 3, 3, 1, 65, 100, countNumImg);
	startImg = LoadGraph("../image/count/start.png");
	endImg = LoadGraph("../image/count/finish.png");

	sceneCun = 0;
	SceneStartFlg = false;
	SceneEndFlg = false;

	endcun = 0;
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
	for (auto e : _enemis) {
		delete e;
	}
	_enemis.clear();
}

//---------------------------------------------------------------------
//　更新
//---------------------------------------------------------------------
void GameScene::Update()
{


	if (!SceneStartFlg)
	{
		SceneCounter();
	}

	EffectManager& efcMng = EffectManager::Instance();
	BloodManager& bloodMng = BloodManager::Instance();
	bool deadFlg = false;
	KeyInput& key = KeyInput::GetInstance();
	Camera& camera = Camera::Instance();
	int windowWidth, windowHeight;
	GetWindowSize(&windowWidth, &windowHeight);

	
		//　更新---------------------------------------------------------------
		_player->Update(SceneStartFlg && !SceneEndFlg);
		for (auto e : _enemis) {
			e->Update();
		}
		for (auto house : _houses) {
			house->Update();
		}
		bloodMng.Update();
		//for (auto cb : _cb1List) {
		//	cb->Update();
		//}
		//eの生成
		//カメラに入っていない位置にらんだむで出現させるンゴ。
		size_t enemyNum_Max = 50;
		if (_enemis.size() < enemyNum_Max) {
			int w, h;
			GetWindowSize(&w, &h);
			float posX = static_cast<float>(rand() % ((_maxLimit - w) * 2) + _minLimit);
			//生成禁止区域なら、なかったことにしちゃお！
			//下駄はかせておく
			if (!(posX > camera.Pos().x - 500.0f) || !(posX < camera.Pos().x + camera.WindowSize().x + 300.0f)) {
				/*EnemyFactorのソースが存在しないので一時コメント*/
				//EnemyFactory& ef = EnemyFactory::Instance();
				//_enemis.push_back(ef.Create(EnemyName::NYN,Vector2(posX,_groundPosY),*_player));
				_enemis.push_back(new EnemyNyn(Vector2(posX, _groundPosY), *_player));
			}
		}
		//houseの生成
		size_t houseNum_Max = 15;
		if (_houses.size() < houseNum_Max) {
			int w, h;
			GetWindowSize(&w, &h);
			float posX = static_cast<float>(rand() % ((_maxLimit - w) * 2) + _minLimit);
			//生成禁止区域なら、なかったことにしちゃお！
			//下駄はかせておく
			if (!(posX > camera.Pos().x - 500.0f) || !(posX < camera.Pos().x + camera.WindowSize().x + 300.0f)) {
				_houses.push_back(new House(Vector2(posX, _groundPosY)));
			}
		}
		//eの死亡確認
		for (auto it = _enemis.begin(); it != _enemis.end();) {
			if ((*it)->GetState() == Enemy::State::isDed) {
				//SE呼び出し
				//キャラクタが持ってた方が可用性は高い、が知らん
				SoundManager::GetInstance().Play(TENKA);
				delete *it;
				it = _enemis.erase(it);
				if (SceneStartFlg)
				{
					++_crusheCount;
				}
				
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
				if (SceneStartFlg)
				{
					++_crusheCount;
				}
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
			//framePos.y = max(min(framePos.y, playerRect.Top()), playerRect.Bottom() - frameSize.y);

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
					houseGroundFlg = true;
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
		//敵
		for (auto e : _enemis) {
			bool eGroundFlg = false;
			Rect2 eRect = e->Rect();
			//飛びすぎちゃうなぁ。
			if (IsHit(_player->Rect(), e->Rect())) {
				e->OnCollided(*_player);
				_player->OnCollided(*e);
			}
			//ground
			if (e->Rect().Bottom() > _groundPosY) {
				eRect.Move(Vector2(0.0f, _groundPosY - e->Rect().Bottom()));
				e->SetRect(eRect);
				eGroundFlg = true;
			}
			e->SetGroundFlag(eGroundFlg);
		}
		
		_player->SetGroundFlg(pgflg);
		//プレイヤーが地面に降り立った瞬間揺れを設定
		if (!_prevPlayerGroundFlg && _player->IsGround()) {
			EffectManager& em = EffectManager::Instance();
			Vector2 pos = _player->Rect().Center();
			pos.y += _player->Rect().H() * 0.25f;
			em.EffectCreate(pos, EFFECT_TYPE::EFFECT_TYPE_SMOKE);
			camera.SetEarthquake(Vector2(0.0f, _player->Vec().y*0.5f));
		}
		_prevPlayerGroundFlg = _player->IsGround();

		efcMng.Update();
		camera.Update();
		//	消滅処理-----------------------------------------------------------
		efcMng.Delete();

		if (timeCun > 0)
		{
			TimeCunter();
		}
		//時間になったら
		if (SceneEndFlg)
		{
			if (--_endTime < 0) {
				SceneManager::GetInstance().ChangeScene(SType_RESULT);
				SoundManager::GetInstance().Stop(BGM_GAME);
			}
		}
}
//---------------------------------------------------------------------
//　時間カウント
//---------------------------------------------------------------------
void GameScene::TimeCunter()
{
	//経過時間
	timeCun = TIME_MAX - (GetNowCount() - timeStart) * 0.001;

}

//---------------------------------------------------------------------
//　始まる前のカウントダウン
//---------------------------------------------------------------------
void GameScene::SceneCounter()
{
	//3秒までに
	if (((GetNowCount() - timeStart) * 0.001) < 3)
	{
		sceneCun = 3 - ((GetNowCount() - timeStart) * 0.001);
	}

	if (((GetNowCount() - timeStart) * 0.001) >= 4)
	{
		SceneStartFlg = true;

		//時間初期化
		timeStart = GetNowCount();
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
	//cameraの移動分/Nで動こうかな（縦はしらん
	//注意点は、画像のサイズは同じにしなきゃってことデス
	//横のみスクロール追加
	Point2 bgSize = { windowW,windowH };
	Point2 bgOffset = -(offset / 4.0f).ToPoint2();
	bgOffset.y = 0.0f;
	Range2 bg = { bgOffset,bgSize };
	DrawExtendGraph(bg.Left(), bg.Top(),bg.Right(),bg.Bottom(),backImg, false);
	if (bg.Left() < 0) {
		bg.Move(bgSize.x,0);
	}
	else {
		bg.Move(-bgSize.x,0);
	}
	DrawExtendGraph(bg.Left(), bg.Top(), bg.Right(), bg.Bottom(), backImg, false);

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
	//e
	for (auto e : _enemis) {
		e->Draw(camera);
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
	//DxLib::DrawBox(_playerInFrame.Left(), _playerInFrame.Top(), _playerInFrame.Right(), _playerInFrame.Bottom(),
		//0xffffffff, false);

	efcMng.Draw(offset);						//エフェクト

	if (!SceneStartFlg)
	{
		if (((GetNowCount() - timeStart) * 0.001) < 3)
		{
			DrawGraph(500, 200, countNumImg[sceneCun], true);
		}


		if (((GetNowCount() - timeStart) * 0.001) >= 3)
		{
			DrawGraph(400, 200, startImg, true);
		}
	}
	else
	{
		//変更●-----
		//score画像
		DrawGraph(10, 10, scoreImg, true);

		DrawGraph(120, 10, numImg[(_crusheCount / 100) % 10], true);
		DrawGraph(156, 10, numImg[(_crusheCount / 10) % 10], true);
		DrawGraph(192, 10, numImg[(_crusheCount / 1) % 10], true);
		//time画像
		DrawGraph(10, 70, timeImg, true);


		int num1;
		int num2;

		if (timeCun > 0)
		{
			num1 = 10 - ((GetNowCount() - timeStart) % 100) / 10;
			num2 = 10 - ((GetNowCount() - timeStart) % 1000) / 100;
		}
		else
		{
			num1 = TIME_MAX;
			num2 = TIME_MAX;
		}


		DrawGraph(120, 70, numImg[(timeCun / 10) % 10], true);
		DrawGraph(156, 70, numImg[(timeCun / 1) % 10], true);

		DrawGraph(192, 70, coronImg, true);

		DrawGraph(228, 70, numImg[(num2 / 1) % 10], true);
		DrawGraph(264, 70, numImg[(num1 / 1) % 10], true);
	}

	//終わる３秒前
	//58
	if (timeCun <= 3)
	{
		//-1回避
		sceneCun = max(timeCun, 0);
		//58
		if (timeCun > 0)
		{
			DrawGraph(500, 200, countNumImg[timeCun-1], true);
		}

		//61
		if (timeCun <= 0)
		{
			DrawGraph(400, 200, endImg, true);
			endcun++;
		}

		if (endcun >= 30)
		{
			SceneEndFlg = true;
		}
	}

	//----------
										//時間描画
	//DxLib::DrawFormatString(10, 40, 0x00000000, "時間：%d:%d%d", timeCun, ((GetNowCount() - timeStart) % 1000) / 100, ((GetNowCount() - timeStart) % 100) / 10);

}