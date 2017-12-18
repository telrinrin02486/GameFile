#include "CB_2.h"

#include <DxLib.h>

CB_2::CB_2(float left_, float top_, float right_, float bottom_) 
	:_lt(left_,top_),_lb(left_,bottom_),_rt(right_,top_),_rb(right_,bottom_){
	_handle = LoadGraph("../image/yaju.jpg");
}
CB_2::CB_2(const Vector2& leftTop_, const Vector2& rightBottom_)
	:_lt(leftTop_),_rb(rightBottom_),_lb(leftTop_.x,rightBottom_.y),_rt(rightBottom_.x,leftTop_.y){
	_handle = LoadGraph("../image/yaju.jpg");
}
CB_2::CB_2(const Vector2& leftTop_, const Vector2& leftBottom_,
	const Vector2& rightTop_, const Vector2& rightBottom_) 
	:_lt(leftTop_),_lb(leftBottom_),_rt(rightTop_),_rb(rightBottom_){

	_handle = LoadGraph("../image/yaju.jpg");

}

CB_2::~CB_2()
{
}

int CB_2::Update() {



	return 0;
}
void CB_2::Draw(const Vector2& offset_) {

	const Vector2 lt = _lt - offset_;
	const Vector2 lb = _lb - offset_;
	const Vector2 rt = _rt - offset_;
	const Vector2 rb = _rb - offset_;

	//ïœå`Ç≥ÇπÇÈÇ∆ï‚ê≥Ç™Ç©Ç©ÇÈ
	//âöÇ›ÇÃïîï™Ç™â~å`Ç…Ç»Ç¡ÇΩÅB
	DrawModiGraphF(lt.x, lt.y, rt.x, rt.y, rb.x, rb.y, lb.x, lb.y,
					_handle, true);

}

void CB_2::LTMove(const Vector2& value_){
	_lt += value_;
}
void CB_2::LBMove(const Vector2& value_) {
	_lb += value_;
}
void CB_2::RTMove(const Vector2& value_) {
	_rt += value_;
}
void CB_2::RBMove(const Vector2& value_) {
	_rb += value_;
}

void CB_2::Move(const Vector2& value_) {
	LTMove(value_);
	LBMove(value_);
	RTMove(value_);
	RBMove(value_);
}