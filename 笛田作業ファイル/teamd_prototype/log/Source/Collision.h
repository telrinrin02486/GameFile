#pragma once

#include "Rect2.h"

//判定
bool IsHit(const Rect2& r1_, const Rect2& r2_);

//重なり矩形の取り出し
Rect2 Overlap(const Rect2& r1_, const Rect2& r2_);

