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

	//当たり判定の部分
	//ダブルディスパッチで
	virtual void OnCollided(const Player& player_) {};
	virtual void OnCollided(const Enemy& enemy_) {};

private:
};

