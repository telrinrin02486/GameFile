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
	//�V�[���؂�ւ��t���O
	_isChange = false;

	//�G�t�F�N�g�Ǘ�
	_effectManager = new EffectManager();

	_player = new Player();


	_cb = new CB_1(*_effectManager);


}

//---------------------------------------------------------------------
//�@�I������
//---------------------------------------------------------------------
void GameScene::Finalize()
{
	//�e��J��
	//�G�t�F�N�g�Ǘ�
	delete _effectManager;
	delete _player;
	delete _cb;

}

//---------------------------------------------------------------------
//�@�X�V
//---------------------------------------------------------------------
void GameScene::Update()
{
	bool deadFlg = false;
	KeyInput& key = KeyInput::GetInstance();
	Camera& camera = Camera::Instance();
	if (key.GetKeyUp(KEY_INPUT_1)) {
		Finalize();
		Initialize();//���Z�b�g
	}
	//�@�X�V---------------------------------------------------------------
	_player->Update();
	
	if (!(deadFlg = _cb->IsDead())) {
		_cb->Update();
	}

	//������Ƃ��낳��
	//����������ŃI�u�W�F�N�g�̕ύX���s����̂�
	//�{�����ł̓_�u���o�b�t�@���z�肳���B
	if (!deadFlg) {
		if (IsHit(_cb->Rect(), _player->Rect())) {
			_cb->Crushed(*_player);
			//�I�u�W�F�N�g�ό`��̏���
			Rect2 ol = Overlap(_cb->Rect(), _player->Rect());
			Vector2 nrmPlayerVec = _player->Vec().Normalize();
			if (IsHit(_cb->Rect(), _player->Rect())) {
				//�t�x��
				nrmPlayerVec = -nrmPlayerVec;
			}
			Vector2 moveValue = nrmPlayerVec * ol.size.Absolute();
			_player->SetPos(_player->Rect().pos + moveValue);

		}
		
	}
	_effectManager	->Update();

	//	���ŏ���-----------------------------------------------------------
	_effectManager	->Delete();
}

//---------------------------------------------------------------------
//�@�`��
//---------------------------------------------------------------------
void GameScene::Draw()
{
	Camera& camera = Camera::Instance();
	Vector2 offset = camera.Pos() + camera.Offset();
	DxLib::DrawGraph( 0, 0, _texID, false );	//�w�i

	_player->Draw(offset);
	if (!(_cb == nullptr)) {
		_cb->Draw(offset);
	}
	_effectManager->Draw();						//�G�t�F�N�g
}