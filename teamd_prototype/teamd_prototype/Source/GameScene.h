#pragma once

#include <list>
#include "Vector2.h"
#include "Rect2.h"

//=====================================================================
//						  GameScene.h
//						�Q�[���Ǘ��N���X
//=====================================================================

//MAX 60�b
#define TIME_MAX 60

class CB_1;
class Player;

class GameScene : public BaseScene
{
private:

	Player		*_player;
	std::list<CB_1*> _cb1List;

	Vector2 _playerStartPos;

	const Rect2 _ground;
	bool _prevPlayerGroundFlg;
	int	_crusheCount;

	//�J�n����
	unsigned int timeStart;
	//�o�ߎ���
	unsigned int timeCun;

	void TimeCunter();

	

public:
	GameScene();	//�R���X�g���N�^
	~GameScene();	//�f�X�g���N�^

	//�@�ʏ�̃��\�b�h-----------------------------------------------------
	void Initialize();	//������
	void Finalize();	//�I������
	void Update();		//�X�V
	void Draw();		//�`��

};