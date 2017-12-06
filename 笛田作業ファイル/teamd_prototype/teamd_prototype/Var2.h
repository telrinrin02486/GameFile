#pragma once

template <typename T>
struct Var2
{
	union {
		T x, y;
		T v[2];
	};
	Var2()
		:x(0), y(0)
	{}
	Var2(const T& x_, const T& y_)
		:x(x_), y(y_)
	{}
	~Var2()
	{}


};

