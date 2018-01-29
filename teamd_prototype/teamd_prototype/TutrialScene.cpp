//=====================================================================
//						  TutrialScene.cpp
//						�`���[�g���A���Ǘ��N���X
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
#include "../House.h"

#include "Collision.h"
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
	
	//�w�i�摜�����[�h
	backImg = LoadGraph("../image/haikei.jpg");
	_player = new Player(Vector2(0.0f,50.0f));
	_player->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });//tutrial�Ȃ̂�startPos�̍Đݒ�
	_prevPlayerGroundFlg = _player->IsGround();

	int w, h;
	GetWindowSize(&w, &h);
	Vector2 pos = { _player->Pos().x - 300, _player->Pos().y };
	house = new House(pos);

	//���̍��W�Z�b�g
	ImageMng::GetInstance()->setUIID("../image/UI/tutrial/yazirusi.png", ID_tut_yazirusi, { pos.x - 100 ,pos.y-100}, pos);
	uiID = ID_tut_text1;
}

//---------------------------------------------------------------------
//�@�I������
//---------------------------------------------------------------------
void TutrialScene::Finalize()
{
	//�e��J��
	delete _player;
	delete house;
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
	if (key.GetKeyUp(KEY_INPUT_TAB))
	{
		SceneManager::GetInstance().ChangeScene(SType_TITLE);
		SoundManager::GetInstance().Stop(BGM_TUTRIAL);
	}
	else
	{
		if (key.GetKeyUp(KEY_INPUT_RETURN) && (uiID < ID_tut_text9))
		{
			uiID++;
		}
		modul1();
		modul2();
		modul3();
		modul4();
		modul5();
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

	//house
	if (house != nullptr)
	{
		house->Draw(camera);
	}

	//�G�t�F�N�g
	efcMng.Draw(offset);
	textDraw(uiID);
}

void TutrialScene::modul1()
{
	if (uiID > ID_tut_text5)
	{
		_player->Update(true);
	}

	if (house != nullptr)
	{
		house->Update();
	}
	if (house != nullptr)
	{
		if (house->IsDead())
		{
			SoundManager::GetInstance().Play(TENKA);
			SoundManager::GetInstance().Play(HIT_1);
			delete house;
			house = nullptr;
		}
	}
}

void TutrialScene::modul2()
{
	//�J�����̈ړ�
	//�J����������
	Camera& camera = Camera::Instance();
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

void TutrialScene::modul3()
{
	if (house != nullptr)
	{
		if (IsHit(house->Rect(), _player->Rect()))
		{
			house->OnCollided(*_player);
		}
	}
}

void TutrialScene::modul4()
{
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
	//������
	if (house != nullptr)
	{
		Rect2 hr = house->Rect();
		bool houseGroundFlg = false;
		//��player
		if (IsHit(_player->Rect(), house->Rect()))
		{
			if (!house->SideHitFlag()) {
				//������͓������Ăق����Ȃ��̂ŁA�ėp�͎g��Ȃ�
				Rect2 ol = Overlap(hr, plr);
				Vector2 cbCenter = hr.Center();
				Vector2 plCenter = plr.Center();
				Vector2 moveValue = Vector2::ZERO;
				Vector2 vec = plCenter - cbCenter;
				//�c�ւ̉����o��
				moveValue.y = ol.Size().y;
				if (vec.y < 0.0f)
				{
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
		if (house->Rect().Bottom() > _groundPosY)
		{
			hr.Move(Vector2(0.0f, _groundPosY - house->Rect().Bottom()));
			house->SetRect(hr);
			houseGroundFlg = true;
		}
		house->SetGroundFlag(houseGroundFlg);
	}
	_player->SetGroundFlg(pgflg);
}

void TutrialScene::modul5()
{
	EffectManager& efcMng = EffectManager::Instance();
	Camera& camera = Camera::Instance();
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

void TutrialScene::textDraw(int id)
{
	ImageMng *ui = ImageMng::GetInstance();
	//mask
	DrawExtendGraph(ui->GetUIID(ID_tut_mask)->posL.x, ui->GetUIID(ID_tut_mask)->posL.y,
					ui->GetUIID(ID_tut_mask)->posR.x, ui->GetUIID(ID_tut_mask)->posR.y,
					ui->GetUIID(ID_tut_mask)->image, true);

	//text
	DrawExtendGraph(ui->GetUIID(id)->posL.x, ui->GetUIID(id)->posL.y,
					ui->GetUIID(id)->posR.x, ui->GetUIID(id)->posR.y,
					ui->GetUIID(id)->image, true);

	if (id == ID_tut_text5)
	{
		//yazirusi
		DrawExtendGraph(ui->GetUIID(ID_tut_yazirusi)->posL.x, ui->GetUIID(ID_tut_yazirusi)->posL.y,
						ui->GetUIID(ID_tut_yazirusi)->posR.x, ui->GetUIID(ID_tut_yazirusi)->posR.y,
						ui->GetUIID(ID_tut_yazirusi)->image, true);
	}

	//if (id == ID_tut_text9)
	//{
	//	//yazirusi
	//	DrawExtendGraph(ui->GetUIID(ID_tut_yazirusi)->posL.x, ui->GetUIID(ID_tut_yazirusi)->posL.y,
	//					ui->GetUIID(ID_tut_yazirusi)->posR.x, ui->GetUIID(ID_tut_yazirusi)->posR.y,
	//					ui->GetUIID(ID_tut_yazirusi)->image, true);
	//}
	
}


