#pragma once

class Rect2;
class Player;
class Enemy;

class Camera;
class EnemyHouse
{
public:
	EnemyHouse();
	~EnemyHouse();

	virtual int Update() = 0;
	virtual void Draw(const Camera& camera_) = 0;

	//�����蔻��̕���
	//�_�u���f�B�X�p�b�`��
	virtual void OnCollided(const Player& player_) {};
	virtual void OnCollided(const Enemy& enemy_) {};

private:
};

