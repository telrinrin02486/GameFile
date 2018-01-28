//=====================================================================
//						  GameScene.cpp
//						�Q�[���Ǘ��N���X
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
#include "../House.h"//�Ȃ������������������Ȃ��Ɣ������Ȃ��B��H
#include "EnemyNyn.h"
#include "../GabyoMan.h"

#include "Collision.h"
#include "SceneManager.h"
#include "../BloodManager.h"

#include "SoundManager.h"
//#include "../EnemyFactory.h"/*EnemyFactor�̃\�[�X�����݂��Ȃ��̂ňꎞ�R�����g*/

constexpr unsigned int ENEMY_MAX = 50;
//---------------------------------------------------------------------
//�@�R���X�g���N�^
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

	_endTime = 60;//�I����̗]�C(�t���[���P��
}

//---------------------------------------------------------------------
//�@�f�X�g���N�^
//---------------------------------------------------------------------
GameScene::~GameScene()
{

}

//---------------------------------------------------------------------
//�@������
//---------------------------------------------------------------------
void GameScene::Initialize()
{
	GameScene();
	EffectManager& efMng = EffectManager::Instance();
	BloodManager& bloodMng = BloodManager::Instance();
	bloodMng.Init();
	int windowWidth, windowHight;
	GetWindowSize(&windowWidth, &windowHight);
	_barrenRange = { _minLimit,_minLimit+400 };//�s�ђn�т̉���
	//�V�[���؂�ւ��t���O
	_isChange = false;
	_crusheCount = 0;
	//��������
	_playerStartPos = Vector2(_minLimit, 50.0f);
	_player = new Player(_playerStartPos);
	_prevPlayerGroundFlg = _player->IsGround();
	//e
	for (int i = 0; i < 30; ++i) {
		int w, h;
		GetWindowSize(&w, &h);
		float posX = static_cast<float>(rand() % ((_maxLimit - w) * 2) + _minLimit);
		//�����֎~���Ȃ�A�Ȃ��������Ƃɂ����Ⴈ�I
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
		//�����֎~���Ȃ�A�Ȃ��������Ƃɂ����Ⴈ�I
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

	
	//�w�i�摜�����[�h
	backImg = LoadGraph("../image/haikei.jpg");
	//house
	for (int i = 0; i < 10; ++i) {
		int w, h;
		GetWindowSize(&w, &h);
		Vector2 pos = { static_cast<float>(rand() % ((_maxLimit - w) * 2) + _minLimit),_groundPosY };
		_houses.push_back(new House(pos));
	}

	//�J�n���Ԃ̎擾
	timeCun = 0;
	timeStart = GetNowCount();

	//�ύX��-------------
	//score�摜
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
	//----------
}

//---------------------------------------------------------------------
//�@�I������
//---------------------------------------------------------------------
void GameScene::Finalize()
{
	//�e��J��

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
//�@�X�V
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

	//result��
	if (key.GetKeyUp(KEY_INPUT_2))
	{
		SceneManager::GetInstance().ChangeScene(SType_RESULT);
		SoundManager::GetInstance().Stop(BGM_GAME);
	}
	else 
	{
		if (key.GetKeyUp(KEY_INPUT_1)) {
			//���ꌋ�\�|���Ȃ��B
			//finalize�Y��Ă��烁�������[�N�N���邶���
			Finalize();
			Initialize();//���Z�b�g
		}
		//�@�X�V---------------------------------------------------------------
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
		//e�̐���
		//�J�����ɓ����Ă��Ȃ��ʒu�ɂ�񂾂ނŏo�������郓�S�B
		size_t enemyNum_Max = 50;
		if (_enemis.size() < enemyNum_Max) {
			int w, h;
			GetWindowSize(&w, &h);
			float posX = static_cast<float>(rand() % ((_maxLimit - w) * 2) + _minLimit);
			//�����֎~���Ȃ�A�Ȃ��������Ƃɂ����Ⴈ�I
			//���ʂ͂����Ă���
			if (!(posX > camera.Pos().x - 500.0f) || !(posX < camera.Pos().x + camera.WindowSize().x + 300.0f)) {
				/*EnemyFactor�̃\�[�X�����݂��Ȃ��̂ňꎞ�R�����g*/
				//EnemyFactory& ef = EnemyFactory::Instance();
				//_enemis.push_back(ef.Create(EnemyName::NYN,Vector2(posX,_groundPosY),*_player));
			}
		}
		//house�̐���
		size_t houseNum_Max = 15;
		if (_houses.size() < houseNum_Max) {
			int w, h;
			GetWindowSize(&w, &h);
			float posX = static_cast<float>(rand() % ((_maxLimit - w) * 2) + _minLimit);
			//�����֎~���Ȃ�A�Ȃ��������Ƃɂ����Ⴈ�I
			//���ʂ͂����Ă���
			if (!(posX > camera.Pos().x - 500.0f) || !(posX < camera.Pos().x + camera.WindowSize().x + 300.0f)) {
				_houses.push_back(new House(Vector2(posX, _groundPosY)));
			}
		}
		//e�̎��S�m�F
		for (auto it = _enemis.begin(); it != _enemis.end();) {
			if ((*it)->GetState() == Enemy::State::isDed) {
				//SE�Ăяo��
				//�L�����N�^�������Ă������p���͍����A���m���
				SoundManager::GetInstance().Play(TENKA);
				delete *it;
				it = _enemis.erase(it);
				if (SceneStartFlg)
				{
					++_crusheCount;
				}
				
				SceneManager::GetInstance().SetScore(_crusheCount);//score�̃Z�b�g
				continue;
			}
			++it;
		}
		//�͂����̎��S�m�F
		for (auto it = _houses.begin(); it != _houses.end();) {
			if ((*it)->IsDead()) {
				SoundManager::GetInstance().Play(HIT_1);
				delete *it;
				it = _houses.erase(it);
				if (SceneStartFlg)
				{
					++_crusheCount;
				}
				SceneManager::GetInstance().SetScore(_crusheCount);//score�̃Z�b�g
				continue;
			}
			++it;
		}
		//�J�����̈ړ�
		//�J����������
		{
			Rect2 playerRect = _player->Rect();
			Vector2 framePos = _playerInFrame.LT() + (camera.Pos() + camera.Offset());
			Vector2 frameSize = _playerInFrame.Size();
			//�J�����̃t���[��������o�Ă���A�����ɍ��킹��悤�Ɉړ�������
			//���v���C���[�̋�`�ɍ��킹��΂����B
			framePos.x = max(min(framePos.x, playerRect.Left()),playerRect.Right() - frameSize.x);
			//framePos.y = max(min(framePos.y, playerRect.Top()), playerRect.Bottom() - frameSize.y);

			Vector2 moveValue = framePos - (_playerInFrame.LT() + (camera.Pos() + camera.Offset()));
			camera.Move(moveValue);
		}
		//�����ɂ��̂������Ȃ�����
		//���̃t���[���̏o�����Ȃ񂾂��A
		//�܂���ɕό`�݂̂���Ă��܂�
		//�ォ�牟���ꂽ�Ƃ��݂̂ɂ��܂���[
		//for (auto cb : _cb1List) {
		//	if (IsHit(cb->Rect(), _player->Rect())) {
		//		Rect2 ol = Overlap(cb->Rect(), _player->Rect());
		//		//Y�̕����ɖ߂�̂Ȃ�AY�������痈�����Ă��ƂŁA�Ԃ����Ⴄ
		//		if (ol.Size().x > ol.Size().y) {
		//			cb->Crushed(*_player);
		//		}
		//	}
		//}
		//house�̂Ԃ�
		//for (auto house : _houses) {
		//	if (IsHit(house->Rect(), _player->Rect())) {
		//		Rect2 ol = Overlap(house->Rect(), _player->Rect());
		//		//Y�̕����ɖ߂�̂Ȃ�AY�������痈�����Ă��ƂŁA�Ԃ����Ⴄ
		//		if (ol.Size().x > ol.Size().y) {
		//			house->Crushed(*_player);
		//		}
		//	}
		//}
		//�����o���֐�
		auto extrusion = [](Rect2& r1_, Rect2& r2_) {
			//����H���ꉟ���o���̂ǂ����悤
			//���ꂶ�ᑊ�肩�����I�ɉ�����Ă�񂾂��ǁB
			Rect2 ol = Overlap(r1_, r2_);
			Vector2 cbCenter = r1_.Center();
			Vector2 plCenter = r2_.Center();
			Vector2 moveValue = Vector2::ZERO;
			Vector2 vec = plCenter - cbCenter;
			//�ǂ̕����ɉ����o�������߂�}���B
			//���ʂƂ��Ă͊O�ώg���̂Ƒ債�ĕς���̂��Ⴄ�H
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
			//�Ƃ肠����1�ڂ𓮂����`�ŁB
			r2_.Move(moveValue);
		};

		//���ɉ����o��
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
		//�����o�����������邽�߂ɍs���Ă�����̂�����
		//�󂪕�����Ȃ��Ȃ��Ă����B
		//�����o�������͒��Ԃɂ��Ȃ��Ƃ��낤����A
		//�����ۂ��Ȃ���A���₷�������ɂ��Ăق����B
		//house��OnCollided
		for (auto house : _houses) {
			if (IsHit(house->Rect(), _player->Rect())) {
				house->OnCollided(*_player);
			}
		}
		//�������火�͉����o���̂݁I�Ƃ��Ȃ�킩��₷������
		Rect2 plr = _player->Rect();
		bool pgflg = false;
		//�v���C���[�ƒn��
		if (_player->Rect().Bottom() >_groundPosY) {
			plr.Move(Vector2(0.0f, _groundPosY - _player->Rect().Bottom()));
			_player->SetRect(plr);
			pgflg = true;
		}
		//������
		for (auto house : _houses) {
			Rect2 hr = house->Rect();
			bool houseGroundFlg = false;
			//��player
			if (IsHit(_player->Rect(), house->Rect())) {
				if (!house->SideHitFlag()) {
					//������͓������Ăق����Ȃ��̂ŁA�ėp�͎g��Ȃ�
					Rect2 ol = Overlap(hr, plr);
					Vector2 cbCenter = hr.Center();
					Vector2 plCenter = plr.Center();
					Vector2 moveValue = Vector2::ZERO;
					Vector2 vec = plCenter - cbCenter;
					//�c�ւ̉����o��
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
			//�ƒn��
			if (house->Rect().Bottom() > _groundPosY) {
				hr.Move(Vector2(0.0f, _groundPosY - house->Rect().Bottom()));
				house->SetRect(hr);
				houseGroundFlg = true;
			}
			house->SetGroundFlag(houseGroundFlg);
		}
		//�G
		for (auto e : _enemis) {
			bool eGroundFlg = false;
			Rect2 eRect = e->Rect();
			//��т������Ⴄ�Ȃ��B
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
		//�v���C���[���n�ʂɍ~�藧�����u�ԗh���ݒ�
		if (!_prevPlayerGroundFlg && _player->IsGround()) {
			camera.SetEarthquake(Vector2(0.0f, 5.0f));
		}
		_prevPlayerGroundFlg = _player->IsGround();

		efcMng.Update();
		camera.Update();
		//	���ŏ���-----------------------------------------------------------
		efcMng.Delete();

		if (timeCun < TIME_MAX)
		{
			TimeCunter();
		}
		//���ԂɂȂ�����
		if (SceneEndFlg)
		{
			if (--_endTime < 0) {
				SceneManager::GetInstance().ChangeScene(SType_RESULT);
				SoundManager::GetInstance().Stop(BGM_GAME);
			}
		}
	}
}
//---------------------------------------------------------------------
//�@���ԃJ�E���g
//---------------------------------------------------------------------
void GameScene::TimeCunter()
{
	//�o�ߎ���
	timeCun = (GetNowCount() - timeStart) * 0.001;

}

//---------------------------------------------------------------------
//�@�n�܂�O�̃J�E���g�_�E��
//---------------------------------------------------------------------
void GameScene::SceneCounter()
{
	//3�b�܂ł�
	if (((GetNowCount() - timeStart) * 0.001) < 3)
	{
		sceneCun = 3 - ((GetNowCount() - timeStart) * 0.001);
	}

	if (((GetNowCount() - timeStart) * 0.001) >= 4)
	{
		SceneStartFlg = true;

		//���ԏ�����
		timeStart = GetNowCount();
	}


}
//---------------------------------------------------------------------
//�@�`��
//---------------------------------------------------------------------
void GameScene::Draw()
{

	//�p�����^�擾���Ȃ���
	EffectManager& efcMng = EffectManager::Instance();
	BloodManager& bloodMng = BloodManager::Instance();
	Camera& camera = Camera::Instance();
	Vector2 offset = camera.Pos() + camera.Offset();
	int windowW, windowH;
	GetWindowSize(&windowW, &windowH);

	DxLib::DrawGraph( 0, 0, _texID, false );	//�w�i
	//�w�i��`�悷�邺
	//camera�̈ړ���/N�œ��������ȁi�c�͂����
	//���ӓ_�́A�摜�̃T�C�Y�͓����ɂ��Ȃ�����Ă��ƃf�X
	//���̂݃X�N���[���ǉ�
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

	//ground�`��
	Rect2 ground = {0.0f,_groundPosY,static_cast<float>(windowW),static_cast<float>(windowH) };
	Vector2 groundOffset = { 0.0f,offset.y };
	ground.Move(-groundOffset);
	DxLib::DrawBox(ground.Left(), ground.Top(), ground.Right(), ground.Bottom(), GetColor(18,198,88), true);
	//�X�R�A���`��
	//DxLib::DrawString(10, 10, "GameScene", 0xffffffff);
	//DxLib::DrawFormatString(10, 25, 0xffffffff, "�j�󐔁F%d", _crusheCount);

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


	//�J�����t���[���͈�
	//DxLib::DrawBox(_playerInFrame.Left(), _playerInFrame.Top(), _playerInFrame.Right(), _playerInFrame.Bottom(),
		//0xffffffff, false);

	efcMng.Draw(offset);						//�G�t�F�N�g

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
		//�ύX��-----
		//score�摜
		DrawGraph(10, 10, scoreImg, true);

		DrawGraph(120, 10, numImg[(_crusheCount / 100) % 10], true);
		DrawGraph(156, 10, numImg[(_crusheCount / 10) % 10], true);
		DrawGraph(192, 10, numImg[(_crusheCount / 1) % 10], true);
		//time�摜
		DrawGraph(10, 70, timeImg, true);


		int num1;
		int num2;

		if (timeCun < TIME_MAX)
		{
			num1 = ((GetNowCount() - timeStart) % 100) / 10;
			num2 = ((GetNowCount() - timeStart) % 1000) / 100;
		}
		else
		{
			num1 = 0;
			num2 = 0;
		}


		DrawGraph(120, 70, numImg[(timeCun / 10) % 10], true);
		DrawGraph(156, 70, numImg[(timeCun / 1) % 10], true);

		DrawGraph(192, 70, coronImg, true);

		DrawGraph(228, 70, numImg[(num2 / 1) % 10], true);
		DrawGraph(264, 70, numImg[(num1 / 1) % 10], true);
	}

	//�I���R�b�O
	//58
	if (timeCun >= (TIME_MAX - 3))
	{
		//-1���
		sceneCun = max(TIME_MAX - timeCun - 1,0);
		//58
		if (((GetNowCount() - timeStart) * 0.001) <= TIME_MAX)
		{
			DrawGraph(500, 200, countNumImg[sceneCun], true);
		}

		//61
		if (((GetNowCount() - timeStart) * 0.001) >= TIME_MAX)
		{
			DrawGraph(400, 200, endImg, true);
		}

		if (((GetNowCount() - timeStart) * 0.001) >= (TIME_MAX + 1))
		{
			SceneEndFlg = true;
		}
	}

	//----------
										//���ԕ`��
	//DxLib::DrawFormatString(10, 40, 0x00000000, "���ԁF%d:%d%d", timeCun, ((GetNowCount() - timeStart) % 1000) / 100, ((GetNowCount() - timeStart) % 100) / 10);

}