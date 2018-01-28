#pragma once

#include <list>
#include "Vector2.h"
#include "Rect2.h"

//=====================================================================
//						  TutrialScene.h
//						�Q�[���Ǘ��N���X
//=====================================================================

//MAX 60�b
#define TIME_MAX 60

class CB_1;
class Player;
class EnemyNyn;
class TutrialScene : public BaseScene
{
private:

	Player	*_player;
	EnemyNyn *enemy;
	

	Vector2 _playerStartPos;
	Rect2	_playerInFrame;//�v���C���[��ǂ�������g�i�J�����p

	float _groundPosY;
	bool _prevPlayerGroundFlg;

	int _minLimit, _maxLimit;



public:
	TutrialScene();	//�R���X�g���N�^
	~TutrialScene();	//�f�X�g���N�^

					//�@�ʏ�̃��\�b�h-----------------------------------------------------
	void Initialize();	//������
	void Finalize();	//�I������
	void Update();		//�X�V
	void Draw();		//�`��

};