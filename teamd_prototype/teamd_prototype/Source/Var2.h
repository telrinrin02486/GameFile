#pragma once

//汎用変数

//テンプレ使った場合、
//必然的にヘッダが大きくなっちゃうゾ～

//こいついつ使うんだゾ・・・

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

