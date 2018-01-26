#pragma once
#include "EnemyHouse.h"
class NormalHouse :
	public EnemyHouse
{
public:
	NormalHouse();
	~NormalHouse();

	int Update() override;
	void Draw(const Camera& camera_) override;


private:

};

