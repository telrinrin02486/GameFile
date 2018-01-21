#pragma once

#include "Vector2.h"

//血
//Enemyから吹き出る
//あしまんはこれを吸収、強化

//量が多いので、処理を一か所にまとめる方法をとってみる

//管理が更新と描画をするぅ
//それ以外に別途方法があるならそれも              

struct Blood
{
	Blood()
		:pos(), vec(),isAlive()
	{}

	//キャストにかかるコストとメモリを圧迫するコスト
	//どっちを優先しようかな

	Point2		pos;//座標
	Point2		vec;//方向
	bool		isAlive;//生死判定



};

