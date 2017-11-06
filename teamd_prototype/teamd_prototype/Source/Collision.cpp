#include "Collision.h"

#include <DxLib.h>

//”»’è
bool IsHit(const Rect2& r1_, const Rect2& r2_) {
	const Rect2& r1 = r1_;
	const Rect2& r2 = r2_;

	return r1.Bottom() > r2.Top() &&
		r1.Right() > r2.Left() &&
		r1.Top() < r2.Bottom() &&
		r1.Left() < r2.Right();
}
//d‚È‚è‹éŒ`‚ÌŽæ‚èo‚µ
Rect2 Overlap(const Rect2& r1_, const Rect2& r2_) {
	const Rect2& r1 = r1_;
	const Rect2& r2 = r2_;

	float left = max(r1.Left(), r2.Left());
	float top = max(r1.Top(), r2.Top());
	float right = min(r1.Right(), r2.Right());
	float bottom = min(r1.Bottom(), r2.Bottom());

	return Rect2(Vector2(left, top), Vector2(right - left, bottom - top));
}