
#include "Range2.h"
#include <DxLib.h>

//操作。
void Range2::Move(const Point2& mValue_) {
	_pos += mValue_;
}
void Range2::Move(int dirX_, int dirY_) {
	_pos += Point2(dirX_, dirY_);
}

void Range2::Teleport(const Point2& pos_) {
	_pos = pos_;
}
void Range2::Teleport(int x_, int y_) {
	_pos = Point2(x_, y_);
}

//描画（ただの矩形描画）
void Range2::Draw(const Point2& offset_, unsigned int color_, bool fillFlag_) const{
	Point2 s = s + offset_;
	Point2 n = n + offset_;
	DrawBox(s.x, s.y, n.x, n.y, color_, fillFlag_);
}