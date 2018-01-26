////#include "typedef.h"
//#include "Vector2.h"
//#include <string>
//#include<memory>
//#pragma once
//
//// ·¬×¸À°‚ÌŒü‚«
//enum DIR {
//	DIR_DOWN,
//	DIR_LEFT,
//	DIR_RIGHT,
//	DIR_UP,
//	DIR_NON,
//	DIR_DETH = DIR_NON,
//	DIR_MAX
//};
//
//class Camera;
//
//class Obj
//{
//public:
//	Obj();
//	~Obj();
//	void init(int setSpeed, Vector2 divSize, Vector2 divCnt, std::string filename, Vector2 chipOffset, int ptnMax);
//	void init(Vector2 divSize, Vector2 divCnt, std::string filename, int setSpeed);
//	int GetSpeed(void);
//	void SetSpeed(int speedNum);
//	Vector2 GetPos(void);
//	void SetPos(Vector2 posMove);
//	Vector2 GetSize(void);
//	virtual void Draw() = 0;
//	virtual void Update() = 0;
//	void Draw(int id);
//	bool GetGameClearFlg(void) { return gameClearFlg; }
//
//private:
//	Vector2 chip;
//	int animPtnMax;
//	int speed;
//	
//
//protected:
//	std::weak_ptr<Camera> cam;
//	const int *image;
//	Vector2 pos;
//	Vector2 posOld;
//	Vector2 size;
//	DIR dir;
//	DIR drawDir;
//	bool drawTurn;
//	unsigned int animCnt;
//	unsigned int animSpeed;
//	bool gameClearFlg;
//};

