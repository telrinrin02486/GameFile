#pragma once

struct Point2
{
	union {
		int x, y;
		int v[2];
	};
	Point2();
	Point2(int x_ = 0, int y_ = 0)
		:x(x_), y(y_)
	{}
	~Point2();


};

