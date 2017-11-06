#include "Rect2.h"

#include <DxLib.h>

void Rect2::Move(const Vector2& dir_) {
	pos += dir_;

}

void Rect2::TelePort(const Vector2& pos_) {
	pos = pos_;
}

void Rect2::TopCrushed(const float y_) {
	pos.y += y_;
	size.y -= y_;
}
void Rect2::BottomCrushed(const float y_) {
	pos.y -= y_;
	size.y += y_;
}
void Rect2::LeftCrushed(const float x_) {
	pos.x += x_;
	size.x -= x_;
}
void Rect2::RightCrushed(const float x_) {
	pos.x -= x_;
	size.x += x_;
}

void Rect2::Draw(const Vector2& offset_,unsigned int color_, bool fillFlag_) const{
	Point2 s = (pos + offset_).ToPoint2();
	Point2 n = (pos + size + offset_).ToPoint2();
	
	DrawBox(s.x,s.y,n.x,n.y,color_, fillFlag_);
}