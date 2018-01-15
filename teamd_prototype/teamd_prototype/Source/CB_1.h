#pragma once

#include "CrushedBox.h"
#include "Rect2.h"

//�����P
//�����Ԃ������B


//�ǉ�(���X��)
//�s���p�^�[��
enum MOVE_PATTERN
{
	MOVE_NORMAL,//�����_���œ���
	MOVE_RETURN,//���}���̂�������Ƃ͋t�ɓ���
};

class Player;

class CB_1 :
	public CrushedBox
{
public:
	
	CB_1(const Rect2& rect_);
	~CB_1()
	{}

	
	//���p�^�[�����Y�ꂽ�B
	//�������Ċm�ۂ������Ȃ�����Ainit�Ńf�[�^��������Ďg���܂킷�B
	void Init(const Rect2& rect_);
	int Update() override;
	void Draw(const Vector2& offset_) override;

	bool IsDead() const {
		return !_alive;
	}

	void Crushed(const Player& player);

	inline const Rect2& Rect() const {
		return _rect;
	}

	//�ǉ�(���X��)
	//MOVE_RETURN�̏���
	void MoveReturnUpdata();


	//�Z�b�^
	void SetRect(const Rect2& rect_) {
		_rect = rect_;
	}
	void SetGroundFlg(bool flg_) {
		_isGround = flg_;
	}
private:
	bool	_isGround;
	int		_handle;
	Rect2		_rect;
	bool		_alive;
	bool		_isRightDir;
	unsigned int	_count;
	Vector2		_vec;
	float		_dirx;
	float		_durability;//�ł�
	int		_hitPoint;
	int		_maxHitPoint;

	//�ǉ�(���X��)
	MOVE_PATTERN pattern;
	const Rect2 *playerPos;

};

