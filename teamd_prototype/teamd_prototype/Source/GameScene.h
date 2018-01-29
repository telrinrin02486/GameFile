#pragma once

#include <list>
#include "Vector2.h"
#include "Rect2.h"

//=====================================================================
//						  GameScene.h
//						�Q�[���Ǘ��N���X
//=====================================================================

//MAX 60�b
#define TIME_MAX 30

class CB_1;
class Player;
class House;
class Enemy;
class EnemyNyn;
class GameScene : public BaseScene
{
private:

	Player		*_player;
	std::list<CB_1*> _cb1List;
	std::list<Enemy*> _enemis;
	std::list<House*> _houses;

	Vector2 _playerStartPos;
	Rect2	_playerInFrame;//�v���C���[��ǂ�������g�i�J�����p
	Point2 _barrenRange;//�����������A�G���킩�Ȃ��͈�
	float _groundPosY;
	bool _prevPlayerGroundFlg;
	int	_crusheCount;

	int _endTime;

	int _minLimit, _maxLimit;

	//�J�n����
	unsigned int timeStart;
	//�o�ߎ���
	unsigned int timeCun;

	void TimeCunter();
	
	//�ύX��-----
	int scoreImg;
	int timeImg;
	int numImg[10];
	int countNumImg[3];
	int startImg;
	int endImg;
	int coronImg;

	void SceneCounter();

	int sceneCun;
	bool SceneStartFlg;
	bool SceneEndFlg;

	int endcun;

	//----------

public:
	GameScene();	//�R���X�g���N�^
	~GameScene();	//�f�X�g���N�^

	//�@�ʏ�̃��\�b�h-----------------------------------------------------
	void Initialize();	//������
	void Finalize();	//�I������
	void Update();		//�X�V
	void Draw();		//�`��

};