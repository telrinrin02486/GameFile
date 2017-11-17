#pragma once
#include "Singleton.h"


class GameMain
	: public Singleton<GameMain>
{
	friend Singleton<GameMain>;
public:
	int Run();

private:
	GameMain();
	~GameMain();



};

