#pragma once
#include "Enemy.h"
#include "Vector2.h"

class TestEnemy :
	public Enemy
{
public:
	TestEnemy();
	~TestEnemy();

	void Update() override;
	void Draw(const Camera& camera_) const override;

private:
	const Vector2 _pos;

};

