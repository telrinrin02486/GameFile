#pragma once
#include "Enemy.h"
#include "Vector2.h"

//うろつく人
class Player;
class NormalHuman :
	public Enemy
{
public:
	NormalHuman(const Player& player_);
	~NormalHuman();

	int Update() override;
	void Draw(const Camera& camera_) const override;
	bool IsAlive() const override;

private:
	const Player& _player;

	bool _isAlive;

	float	_speed;//動くスピード

	bool	_isGround;
	int		_handle;
	Rect2		_rect;
	bool		_isRightDir;
	unsigned int	_count;
	Vector2		_vec;
	float		_dirx;

	float		_durability;//固さ
	int		_hitPoint;
	int		_maxHitPoint;

};

