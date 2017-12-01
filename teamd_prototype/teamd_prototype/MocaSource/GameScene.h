#pragma once

#include "Vector2.h"
#include "Rect2.h"
//=====================================================================
//						  GameScene.h
//						�Q�[���Ǘ��N���X
//=====================================================================

class CB_1;
class Player;
class EnemyManager;
class GameScene : public BaseScene
{
private:
	EffectManager	*_effectManager;

	CB_1		*_cb;
	Player		*_player;

	EnemyManager *_EM;//�ǋL

	Vector2 _playerStartPos;
	Rect2 _cbStartRect;

public:
	GameScene();	//�R���X�g���N�^
	~GameScene();	//�@�f�X�g���N�^

	//�@�ʏ�̃��\�b�h-----------------------------------------------------
	void Initialize();	//������
	void Finalize();	//�I������
	void Update();		//�X�V
	void Draw();		//�`��

	//�@�A�N�Z�T-----------------------------------------------------------
	EffectManager	*GetEffectMng()	{ return _effectManager; }
};