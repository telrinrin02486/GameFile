//=====================================================================
//						  TutrialScene.cpp
//						�Q�[���Ǘ��N���X
//=====================================================================
using namespace std;

// TutrialScene.h
#include "BaseScene.h"
#include "Vector2.h"			// �g�p�Ȃ�
#include "Effect.h"				// Vector2
#include "EffectManager.h"		// Effect�AVector2�Astd
#include "ImageMng.h"
#include "TutrialScene.h"			// BaseScene�AEffectManager

// TutrialScene.cpp
#include "KeyInput.h"		// �g�p�Ȃ�
#include "DxLib.h"

#include "Camera.h"

#include "Player.h"

#include "SceneManager.h"
#include "SoundManager.h"

//---------------------------------------------------------------------
//�@�R���X�g���N�^
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
//�@�f�X�g���N�^
//---------------------------------------------------------------------
TutrialScene::~TutrialScene()
{
}

//---------------------------------------------------------------------
//�@������
//---------------------------------------------------------------------
void TutrialScene::Initialize()
{
	EffectManager& efMng = EffectManager::Instance();
	//�w�i�摜�����[�h
	backImg = LoadGraph("../image/haikei.jpg");

	_player = new Player(Vector2(0.0f, 50.0f));
	_player->SetPos({ WINDOW_WIDTH  / 2, WINDOW_HEIGHT  / 2});//tutrial�Ȃ̂�startPos�̍Đݒ�
	_prevPlayerGroundFlg = _player->IsGround();
	
	int w, h;
	GetWindowSize(&w, &h);
	Vector2 pos = { _player->Pos().x, _player->Pos().y };
	//enemy = new EnemyNyn(pos, *_player);
	
}

//---------------------------------------------------------------------
//�@�I������
//---------------------------------------------------------------------
void TutrialScene::Finalize()
{
	//�e��J��

	delete _player;

	//delete enemy;
}

//---------------------------------------------------------------------
//�@�X�V
//---------------------------------------------------------------------
void TutrialScene::Update()
{
	EffectManager& efcMng = EffectManager::Instance();
	bool deadFlg = false;
	KeyInput& key = KeyInput::GetInstance();
	Camera& camera = Camera::Instance();
	int windowWidth, windowHeight;
	GetWindowSize(&windowWidth, &windowHeight);

	//title��
	if (key.GetKeyUp(KEY_INPUT_RETURN))
	{
		SceneManager::GetInstance().ChangeScene(SType_TITLE);
		SoundManager::GetInstance().Stop(BGM_TUTRIAL);
	}
	else
	{
		
		//�@�X�V---------------------------------------------------------------
		_player->Update(true);
		//enemy->Update();
	
		
		
		//�J�����̈ړ�
		//�J����������
		{
			Rect2 playerRect = _player->Rect();
			Vector2 framePos = _playerInFrame.LT() + (camera.Pos() + camera.Offset());
			Vector2 frameSize = _playerInFrame.Size();
			//�J�����̃t���[��������o�Ă���A�����ɍ��킹��悤�Ɉړ�������
			//���v���C���[�̋�`�ɍ��킹��΂����B
			framePos.x = max(min(framePos.x, playerRect.Left()), playerRect.Right() - frameSize.x);
			framePos.y = max(min(framePos.y, playerRect.Top()), playerRect.Bottom() - frameSize.y);

			Vector2 moveValue = framePos - (_playerInFrame.LT() + (camera.Pos() + camera.Offset()));
			camera.Move(moveValue);
		}
		
		
		//�������火�͉����o���̂݁I�Ƃ��Ȃ�킩��₷������
		Rect2 plr = _player->Rect();
		bool pgflg = false;

		//�v���C���[�ƒn��
		if (_player->Rect().Bottom() >_groundPosY) 
		{
			plr.Move(Vector2(0.0f, _groundPosY - _player->Rect().Bottom()));
			_player->SetRect(plr);
			pgflg = true;
		}
		
		
		_player->SetGroundFlg(pgflg);
		//�v���C���[���n�ʂɍ~�藧�����u�ԗh���ݒ�
		if (!_prevPlayerGroundFlg && _player->IsGround()) 
		{
			camera.SetEarthquake(Vector2(0.0f, 5.0f));
		}
		_prevPlayerGroundFlg = _player->IsGround();

		efcMng.Update();
		camera.Update();

		//	���ŏ���-----------------------------------------------------------
		efcMng.Delete();

	}
}

//---------------------------------------------------------------------
//�@�`��
//---------------------------------------------------------------------
void TutrialScene::Draw()
{

	//�p�����^�擾���Ȃ���
	EffectManager& efcMng = EffectManager::Instance();
	Camera& camera = Camera::Instance();
	Vector2 offset = camera.Pos() + camera.Offset();
	int windowW, windowH;
	GetWindowSize(&windowW, &windowH);

	//�w�i��`�悷�邺										
	DrawExtendGraph(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, backImg, false);

	//ground�`��
	Rect2 ground = { 0.0f,_groundPosY,static_cast<float>(windowW),static_cast<float>(windowH) };
	Vector2 groundOffset = { 0.0f,offset.y };
	ground.Move(-groundOffset);
	DxLib::DrawBox(ground.Left(), ground.Top(), ground.Right(), ground.Bottom(), 0xff0fff0f, true);
	
	//player
	_player->Draw(offset);
	//enemy
	//enemy->Draw();
	
	//�G�t�F�N�g
	efcMng.Draw(offset);						

	
}