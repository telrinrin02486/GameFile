#pragma once

#include "Vector2.h"

//‰ó‚ê‚é” ‚ÌŠî‘b
class CrushedBox
{
public:
	CrushedBox();
	virtual ~CrushedBox();

	virtual int Update() = 0;
	virtual void Draw(const Vector2& offset_) = 0;

private:


};

