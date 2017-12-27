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

#include "Collision.h"

//---------------------------------------------------------------------
//�@�R���X�g���N�^
//---------------------------------------------------------------------
GameScene::GameScene()
	:_ground(0,400,2000,1000)
{

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
	//�V�[���؂�ւ��t���O
	_isChange = false;
	_crusheCount = 0;

	_player = new Player();
	_prevPlayerGroundFlg = _player->IsGround();

	for (int i = 0; i < 3; ++i) {
		float rSize = static_cast<float>((rand() % 150) + 15);
		_cb1List.push_back(new CB_1(Rect2(Vector2(static_cast<float>(rand() % 1000), 300.0f), Vector2(rSize, rSize))));
	}

	
	//�w�i�摜�����[�h
	backImg = LoadGraph("../image/haikei.jpg");
	
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

	if (key.GetKeyUp(KEY_INPUT_1)) {
		//���ꌋ�\�|���Ȃ��B
		//finalize�Y��Ă��烁�������[�N�N���邶���
		Finalize();
		Initialize();//���Z�b�g
	}
	//�@�X�V---------------------------------------------------------------
	_player->Update();

	for (auto cb : _cb1List) {
		cb->Update();
	}
	for (auto it = _cb1List.begin(); it != _cb1List.end();) {
		if ((*it)->IsDead()) {
			float rSize = static_cast<float>((rand() % 150) + 15);
			(*it)->Init(Rect2(Vector2(rand() % 1000, 300),Vector2(rSize,rSize)));
			++_crusheCount;
			continue;
		}
		++it;
	}
	//if (!(deadFlg = _cb->IsDead())) {
	//	_cb->Update();
	//}
	//�����ɂ��̂������Ȃ�����
	//���̃t���[���̏o�����Ȃ񂾂��A
	//�܂���ɕό`�݂̂���Ă��܂�
	//�ォ�牟���ꂽ�Ƃ��݂̂ɂ��܂���[
	for (auto cb : _cb1List) {
		if (IsHit(cb->Rect(), _player->Rect())) {
			Rect2 ol = Overlap(cb->Rect(), _player->Rect());
			//Y�̕����ɖ߂�̂Ȃ�AY�������痈�����Ă��ƂŁA�Ԃ����Ⴄ
			if (ol.Size().x > ol.Size().y) {
				cb->Crushed(*_player);
			}
		}
	}
	//�����o���֐�
	auto extrusion = [](Rect2& r1_, Rect2& r2_){
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
	Rect2 plr = _player->Rect();
	Rect2 grdr = _ground;
	bool pgflg = false;
	
	//���ɉ����o��
	for (auto cb : _cb1List) {
		Rect2 cbr = cb->Rect();
		//player
		if (IsHit(_player->Rect(),cb->Rect())) {
			extrusion(cbr,plr);
			_player->SetRect(plr);
			pgflg = true;
		}
		//ground
		if (IsHit(cb->Rect(), _ground)) {
			extrusion(grdr,cbr);
			cb->SetRect(cbr);
			cb->SetGroundFlg(true);
		}
		else {
			cb->SetGroundFlg(false);
		}
	}
	//
	if (IsHit(_player->Rect(), _ground)) {
		extrusion(grdr,plr);
		_player->SetRect(plr);
		pgflg = true;
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
}

//---------------------------------------------------------------------
//�@�`��
//---------------------------------------------------------------------
void GameScene::Draw()
{
	//�w�i��`�悷�邺
	DrawGraph(0, 0, backImg, false);

	EffectManager& efcMng = EffectManager::Instance();
	Camera& camera = Camera::Instance();
	Vector2 offset = camera.Pos() + camera.Offset();
	DxLib::DrawGraph( 0, 0, _texID, false );	//�w�i
	Rect2 ground = _ground;
	ground.Move(offset);
	DrawBox(ground.Left(), ground.Top(), ground.Right(), ground.Bottom(), 0xff0fff0f, true);

	DrawString(10, 10, "GameScene", 0xffffffff);
	DrawFormatString(10, 25, 0xffffffff, "�j�󐔁F%d", _crusheCount);
	_player->Draw(offset);
	for (auto cb : _cb1List) {
		cb->Draw(offset);
		const Rect2 cbr = cb->Rect();
		DrawBox(cbr.Left(), cbr.Top(), cbr.Right(), cbr.Bottom(), 0xf0f0f0ff, false);
	}
	//if (!(_cb == nullptr)) {
	//	_cb->Draw(offset);
	//}
	efcMng.Draw();						//�G�t�F�N�g


	
}