#pragma once

#include "Singleton.h"
class GameMain:
	public Singleton<GameMain>
{
	friend Singleton<GameMain>;
public:
	GameMain();
	~GameMain();

	int Init();
	int Update();
	int Draw();
	void End();
private:

};

