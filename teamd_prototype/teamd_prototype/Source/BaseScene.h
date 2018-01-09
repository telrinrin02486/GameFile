#pragma once
//===================================================================
//						BaseScene.h
//					   Base基底クラス
//===================================================================

class BaseScene
{
private:

protected:
	int _texID;
	bool _isChange;

	
	int backImg;//背景画像

public:
	//純粋仮想関数
	//継承先によって処理が変わる
	//継承先で必ず同じ関数を実装する必要がある
	virtual void Initialize()	= 0;
	virtual void Update()		= 0;
	virtual void Draw()			= 0;
};