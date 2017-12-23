#pragma once

#include "Vector2.h"
#include "Range2.h"


//��]�ւ̑Ή��͂ǂ��������ȁB
//��`���Ė��O������ꕾ�����܂��
//�͈͂ł������B
//��`�͉�]����ׂ����낤�Ȃ��B
//�`��̕��ŉ�]��\�����Ă���Ă�ꍇ������A
//�������������Ă�K�v���Ȃ��ꍇ������B
//�ʁ`��

//�ǂ������`����ł�����Ă������A
//�ۑ����͈�Ԍy���������B

//�����o�ϐ��𒼐ڐG��񂶂�˂��X�e�n�Q�I
//�ύX���ǂ����񂾱ʧ݁I�H�i���߁j
class Rect2
{
public:
	Rect2(float x_, float y_, float w_, float h_)
		:_pos(x_, y_), _size(w_, h_)
	{}
	Rect2(const Vector2& pos_, const Vector2& size_)
		:_pos(pos_), _size(size_)
	{}

	void Move(const Vector2& dir_);
	void Move(float x_, float y_);
	void TelePort(const Vector2& pos_);
	void TelePort(float x_, float y_);

	void TopCrushed(const float y_);
	void BottomCrushed(const float y_);
	void LeftCrushed(const float x_);
	void RightCrushed(const float x_);

	inline float Left() const { return _pos.x; }
	inline float Right() const { return _pos.x + _size.x; }
	inline float Top() const { return _pos.y; }
	inline float Bottom() const { return _pos.y + _size.y; }
	
	inline Vector2 LT() const { return Vector2(Left(), Top()); }
	inline Vector2 LB() const { return Vector2(Left(), Bottom()); }
	inline Vector2 RT() const { return Vector2(Right(), Top()); }
	inline Vector2 RB() const { return Vector2(Right(), Bottom()); }

	inline Vector2 Center() const {
		return Vector2(
			Right() - Size().x * 0.5f,
			Bottom() - Size().y * 0.5f
			);
	}
	inline Vector2 Size() const {
		return Vector2(Right() - Left(), Bottom() - Top());
	}
	//����
	inline bool IsFlont() const {
		return (!(Right() < Left()) || !(Bottom() < Top()));
	}

	void Draw(const Vector2& offset_,unsigned int color_ = 0xffffffff, bool fillFlag_ = true) const;

private:
	Vector2		_pos;
	Vector2		_size;
};

