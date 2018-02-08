#pragma once

#include <list>
#include "Vector2.h"
#include "Rect2.h"

//=====================================================================
//						  TutrialScene.h
//						�`���[�g���A���Ǘ��N���X
//=====================================================================

//MAX 60�b
#define TIME_MAX 60

class CB_1;
class Player;
class House;
class EnemyNyn;
class TutrialScene : public BaseScene
{
private:

	Player		*_player;
	House		*house;
	int uiID;
	bool tutFlag;

	Vector2 _playerStartPos;
	Rect2	_playerInFrame;//�v���C���[��ǂ�������g�i�J�����p

	float _groundPosY;
	bool _prevPlayerGroundFlg;

	int _minLimit, _maxLimit;

	int nowPad, oldPad;
	bool weigStep;
	Vector2 yaziPos;

public:
	TutrialScene();	//�R���X�g���N�^
	~TutrialScene();	//�f�X�g���N�^

					//�@�ʏ�̃��\�b�h-----------------------------------------------------
	void Initialize();	//������
	void Finalize();	//�I������
	void Update();		//�X�V
	void Draw();		//�`��
	void modul1();
	void modul2();
	void modul3();
	void modul4();
	void modul5();
	void textDraw(int id, const Vector2 offset_);
};