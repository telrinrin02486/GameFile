#include "Rect2.h"

#include <DxLib.h>

void Rect2::Move(const Vector2& dir_) {
	_pos += dir_;

}
void Rect2::Move(float x_, float y_) {
	_pos += Vector2(x_, y_);
}
void Rect2::TelePort(const Vector2& pos_) {
	_pos = pos_;
}
void Rect2::TelePort(float x_, float y_) {
	_pos = Vector2(x_, y_);
}
void Rect2::TopCrushed(const float y_) {
	_pos.y += y_;
	_size.y -= y_;
}
void Rect2::BottomCrushed(const float y_) {
	_pos.y -= y_;
	_size.y += y_;
}
void Rect2::LeftCrushed(const float x_) {
	_pos.x += x_;
	_size.x -= x_;
}
void Rect2::RightCrushed(const float x_) {
	_pos.x -= x_;
	_size.x += x_;
}

void Rect2::Draw(const Vector2& offset_,unsigned int color_, bool fillFlag_) const{
	Point2 s = (_pos + offset_).ToPoint2();
	Point2 n = (_pos + _size + offset_).ToPoint2();
	
	DrawBox(s.x,s.y,n.x,n.y,color_, fillFlag_);
}