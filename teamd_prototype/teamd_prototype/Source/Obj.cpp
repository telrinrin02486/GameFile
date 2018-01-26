//using namespace std;
//#include "ImageMng.h"
//#include "obj.h"
//#include "Player.h"
//#include "EditCursor.h"
//#include "Camera.h"
////#include "init.h"
////#include "Main.h"
//#include "Vector2.h"
//#include "Dxlib.h"	// DxLib×²ÌÞ×Ø‚ðŽg—p‚·‚é
//
//Obj::Obj()
//{
//	image	= NULL;
//	pos		= { 0,0 };
//	dir		= DIR_NON;
//	drawDir = DIR_DOWN;
//	animCnt = 0;
//	animSpeed = 10;
//	gameClearFlg = false;
//}
//
//Obj::~Obj()
//{
//}
//
//void Obj::init(int setSpeed, Vector2 divSize, Vector2 divCnt, string filename, Vector2 chipOffset, int ptnMax)
//{
//	image = ImageMng::GetInstance()->GetImageID(filename, divCnt, divSize);
//	size = divSize;
//	chip = chipOffset;
//	animPtnMax = ptnMax;
//	SetSpeed(setSpeed);
//}
//
//void Obj::init(Vector2 divSize, Vector2 divCnt, string filename, int setSpeed)
//{
//	image = ImageManager::GetInstance()->GetImageID(filename, divCnt, divSize);
//	size = divSize;
//	SetSpeed(setSpeed);
//}
//
//
//int Obj::GetSpeed(void)
//{
//	return speed;
//}
//
//void Obj::SetSpeed(int speedNum)
//{
//	speed = speedNum;
//}
//
//Vector2 Obj::GetSize(void)
//{
//	return size;
//}
//
//Vector2 Obj::GetPos(void)
//{
//	return pos;
//}
//
//void Obj::SetPos(Vector2 posMove)
//{
//	pos = posMove;
//}
//
//void Obj::Draw(int id)
//{
//	if (image == NULL)
//	{
//		return;
//	}
//	Vector2 camSize = cam.lock()->GetGmScrSize();
//	Vector2 scrPos  = cam.lock()->GetPos();
//	scrPos.x -= (camSize.x / 2);
//	scrPos.y -= (camSize.y / 2);
//	
//	if (((pos.x) >= scrPos.x-size.x*2) && (pos.x - scrPos.x <= SCREEN_SIZE_X )
//	 && ((pos.y - size.y) >= scrPos.y) && (pos.y <= scrPos.y + camSize.y))
//	{
//		if (!drawTurn)
//		{
//			DrawGraph((SCREEN_SIZE_X - camSize.x) / 2 + pos.x - scrPos.x, pos.y - scrPos.y, image[id], true);
//		}
//		else
//		{
//			DrawTurnGraph((SCREEN_SIZE_X - camSize.x) / 2 + pos.x - scrPos.x, pos.y - scrPos.y, image[id], true);
//		}
//	}
//}