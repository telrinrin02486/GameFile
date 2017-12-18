#include "Collision.h"

#include <DxLib.h>

#include "Range2.h"
#include "Rect2.h"

//生成する際の形に依存してしまう。

//判定
bool IsHit(const Rect2& r1_, const Rect2& r2_) {
	const Rect2& r1 = r1_;
	const Rect2& r2 = r2_;

	return r1.Bottom() > r2.Top() &&
		r1.Right() > r2.Left() &&
		r1.Top() < r2.Bottom() &&
		r1.Left() < r2.Right();
}
bool IsHit(const Range2& r1_, const Range2& r2_) {
	const Range2& r1 = r1_;
	const Range2& r2 = r2_;

	return r1.Bottom() > r2.Top() &&
		r1.Right() > r2.Left() &&
		r1.Top() < r2.Bottom() &&
		r1.Left() < r2.Right();
}

//重なり矩形の取り出し
Rect2 Overlap(const Rect2& r1_, const Rect2& r2_) {
	const Rect2& r1 = r1_;
	const Rect2& r2 = r2_;

	float left = max(r1.Left(), r2.Left());
	float top = max(r1.Top(), r2.Top());
	float right = min(r1.Right(), r2.Right());
	float bottom = min(r1.Bottom(), r2.Bottom());

	return Rect2(Vector2(left, top), Vector2(right - left, bottom - top));
}
Range2 Overlap(const Range2& r1_, const Range2& r2_) {
	const Range2& r1 = r1_;
	const Range2& r2 = r2_;

	float left = max(r1.Left(), r2.Left());
	float top = max(r1.Top(), r2.Top());
	float right = min(r1.Right(), r2.Right());
	float bottom = min(r1.Bottom(), r2.Bottom());

	return Range2(Point2(left, top), Point2(right - left, bottom - top));
}