#pragma once

#include <list>
#include "Vector2.h"
#include "Rect2.h"

//=====================================================================
//						  GameScene.h
//						�Q�[���Ǘ��N���X
//=====================================================================

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
public:
	GameScene();	//�R���X�g���N�^
	~GameScene();	//�@�f�X�g���N�^

	//�@�ʏ�̃��\�b�h-----------------------------------------------------
	void Initialize();	//������
	void Finalize();	//�I������
	void Update();		//�X�V
	void Draw();		//�`��

};