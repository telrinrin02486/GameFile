//=====================================================================
//						  GameScene.cpp
//						�Q�[���Ǘ��N���X
//=====================================================================
using namespace std;

// GameScene.h
#include "BaseScene.h"
#include "Vector2.h"			// �g�p�Ȃ�
#include "Effect.h"				// Vector2
#include "EffectManager.h"		// Effect�AVector2�Astd
#include "GameScene.h"			// BaseScene�AEffectManager

// GameScene.cpp
#include "KeyInput.h"		// �g�p�Ȃ�
#include "DxLib.h"

#include "Camera.h"

#include "Player.h"
#include "CB_1.h"
#include "../House.h"//�Ȃ������������������Ȃ��Ɣ������Ȃ��B��H
#include "EnemyNyn.h"

#include "Collision.h"
#include "SceneManager.h"
#include "../BloodManager.h"

//---------------------------------------------------------------------
//�@�R���X�g���N�^
//---------------------------------------------------------------------
GameScene::GameScene()
	:_playerInFrame(170,50,0,0)
{
	_groundPosY = 400.0f;
	int w, h;
	GetWindowSize(&w, &h);
	_playerInFrame.ReSize(Vector2(w - 340, (h/3)*2));

	_minLimit = -2000;
	_maxLimit = static_cast<float>(w) + 2000;
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
	EffectManager& efMng = EffectManager::Instance();
	BloodManager& bloodMng = BloodManager::Instance();

	//�V�[���؂�ւ��t���O
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

	
	//�w�i�摜�����[�h
	backImg = LoadGraph("../image/haikei.jpg");
	
	for (int i = 0; i < 10; ++i) {
		int w, h;
		GetWindowSize(&w, &h);
		Vector2 pos = { static_cast<float>(rand() % ((_maxLimit - w) * 2) + _minLimit),static_cast<float>(rand() % h) };
		_houses.push_back(new House(pos));
	}
	//�J�n���Ԃ̎擾
	timeCun = 0;
	timeStart = GetNowCount();
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
	for (auto e : _nyns) {
		delete e;
	}
	_nyns.clear();
}

//---------------------------------------------------------------------
//�@�X�V
//---------------------------------------------------------------------
void GameScene::Update()
{
	EffectManager& efcMng = EffectManager::Instance();
	bool deadFlg = false;
	KeyInput& key = KeyInput::GetInstance();
	Camera& camera = Camera::Instance();
	int windowWidth, windowHeight;
	GetWindowSize(&windowWidth, &windowHeight);

	//result��
	if (key.GetKeyUp(KEY_INPUT_2))
	{
		SceneManager::GetInstance().ChangeScene(SType_RESULT);
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
		_player->Update();
		for (auto nyn : _nyns) {
			nyn->Update();
		}
		for (auto house : _houses) {
			house->Update();
		}
		//for (auto cb : _cb1List) {
		//	cb->Update();
		//}
		//nyn�̎��S�m�F
		for (auto it = _nyns.begin(); it != _nyns.end();) {
			if ((*it)->GetState() == Enemy::State::isDed) {
				delete *it;
				it = _nyns.erase(it);
				++_crusheCount;
				SceneManager::GetInstance().SetScore(_crusheCount);//score�̃Z�b�g
				continue;
			}
			++it;
		}
		//�͂����̎��S�m�F
		for (auto it = _houses.begin(); it != _houses.end();) {
			if ((*it)->IsDead()) {
				delete *it;
				it = _houses.erase(it);
				++_crusheCount;
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
			framePos.y = max(min(framePos.y, playerRect.Top()), playerRect.Bottom() - frameSize.y);

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
		//nyn
		for (auto nyn : _nyns) {
			bool nynGroundFlg = false;
			Rect2 nynRect = nyn->Rect();
			//��т������Ⴄ�Ȃ��B
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
		//�v���C���[���n�ʂɍ~�藧�����u�ԗh���ݒ�
		if (!_prevPlayerGroundFlg && _player->IsGround()) {
			camera.SetEarthquake(Vector2(0.0f, 5.0f));
		}
		_prevPlayerGroundFlg = _player->IsGround();

		efcMng.Update();
		camera.Update();
		//	���ŏ���-----------------------------------------------------------
		efcMng.Delete();


		TimeCunter();
	}
}
//---------------------------------------------------------------------
//�@���ԃJ�E���g
//---------------------------------------------------------------------
void GameScene::TimeCunter()
{
	//�o�ߎ���
	timeCun = (GetNowCount() - timeStart) * 0.001;

	//���ԂɂȂ�����
	if (timeCun >= TIME_MAX)
	{

	}


}
//---------------------------------------------------------------------
//�@�`��
//---------------------------------------------------------------------
void GameScene::Draw()
{

	//�p�����^�擾���Ȃ���
	EffectManager& efcMng = EffectManager::Instance();
	Camera& camera = Camera::Instance();
	Vector2 offset = camera.Pos() + camera.Offset();
	int windowW, windowH;
	GetWindowSize(&windowW, &windowH);

	DxLib::DrawGraph( 0, 0, _texID, false );	//�w�i
	//�w�i��`�悷�邺
	DrawExtendGraph(0, 0,windowW,windowH,backImg, false);
	//ground�`��

	Rect2 ground = {0.0f,_groundPosY,static_cast<float>(windowW),static_cast<float>(windowH) };
	Vector2 groundOffset = { 0.0f,offset.y };
	ground.Move(-groundOffset);
	DxLib::DrawBox(ground.Left(), ground.Top(), ground.Right(), ground.Bottom(), 0xff0fff0f, true);
	//�X�R�A���`��
	//DxLib::DrawString(10, 10, "GameScene", 0xffffffff);
	DxLib::DrawFormatString(10, 25, 0xffffffff, "�j�󐔁F%d", _crusheCount);

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
	
	//cb
	//for (auto cb : _cb1List) {
	//	cb->Draw(offset);
	//	Rect2 cbr = cb->Rect();
	//	cbr.Move(-offset);
	//	DxLib::DrawBox(cbr.Left(), cbr.Top(), cbr.Right(), cbr.Bottom(), 0xf0f0f0ff, false);
	//}


	//�J�����t���[���͈�
	//DxLib::DrawBox(_playerInFrame.Left(), _playerInFrame.Top(), _playerInFrame.Right(), _playerInFrame.Bottom(),
	//	0xffffffff, false);

	efcMng.Draw(offset);						//�G�t�F�N�g

										//���ԕ`��
	DxLib::DrawFormatString(10, 40, 0x00000000, "���ԁF%d:%d%d", timeCun, ((GetNowCount() - timeStart) % 1000) / 100, ((GetNowCount() - timeStart) % 100) / 10);
	
}