#pragma once

//�ėp�ϐ�

//�e���v���g�����ꍇ�A
//�K�R�I�Ƀw�b�_���傫���Ȃ����Ⴄ�]�`

//�������g���񂾃]�E�E�E

template <typename T>
struct Var2
{
	union {
		struct {
			T x;
			T y;

		};
		T v[2];
	};
	Var2()
		:x(), y()
	{}
	Var2(const T& x_, const T& y_)
		:x(x_), y(y_)
	{}
	~Var2()
	{}



};

