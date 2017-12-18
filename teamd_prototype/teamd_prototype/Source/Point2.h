#pragma once

struct Point2
{
	union {
		struct {
			int x;
			int y;
		};
		int v[2];
	};
	Point2()
		:x(), y()
	{}
	Point2(int x_, int y_)
		:x(x_), y(y_)
	{}
	~Point2()
	{}


	Point2& operator+=(const Point2& other_);
	Point2& operator-=(const Point2& other_);
	Point2& operator+=(int other_);
	Point2& operator-=(int other_);
	Point2& operator*=(int other_);
	Point2& operator/=(int other_);
	Point2& operator%=(int other_);

	bool operator==(const Point2& other_) const;
	bool operator!=(const Point2& other_) const;
	bool operator<(const Point2& other_) const;
	bool operator>(const Point2& other_) const;
	bool operator<=(const Point2& other_) const;
	bool operator>=(const Point2& other_) const;

	Point2& operator-();

	Point2 Absolute() const;
};

Point2 operator+(const Point2& l_, const Point2& r_);
Point2 operator-(const Point2& l_, const Point2& r_);

Point2 operator+(const Point2& l_, int r_);
Point2 operator-(const Point2& l_, int r_);
Point2 operator*(const Point2& l_, int r_);
Point2 operator/(const Point2& l_, int r_);
Point2 operator%(const Point2& l_, int r_);