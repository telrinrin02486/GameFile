#pragma once
#include "CrushedBox.h"

#include "Vector2.h"

//端っこがへこむ君。
class CB_2 :
	public CrushedBox
{
public:
	CB_2(float left_, float top_, float right_, float bottom_);
	CB_2(const Vector2& leftTop_, const Vector2& rightBottom_);
	CB_2(const Vector2& leftTop_, const Vector2& leftBottom_, 
		const Vector2& rightTop_, const Vector2& rightBottom_ );

	~CB_2();


	int Update() override;
	void Draw(const Vector2& offset_) override;

	void LTMove(const Vector2& value_);
	void LBMove(const Vector2& value_);
	void RTMove(const Vector2& value_);
	void RBMove(const Vector2& value_);

	void Move(const Vector2& value_);
private:
	//各頂点、
	Vector2 _lt, _lb, _rt, _rb;

	int	_handle;

};

