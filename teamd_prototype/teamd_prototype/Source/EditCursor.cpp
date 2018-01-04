//using namespace std;
//#include <string>
//#include "ImageManager.h"
//#include "dxlib.h"
//#include "typedef.h"
//#include "Camera.h"
//#include "MapCtl.h"
//#include "EditCursor.h"
//
//
//EditCursor::EditCursor(std::weak_ptr<MapCtl> mapPtr, std::weak_ptr<Camera> camPtr)
//{
//	cam = camPtr;
//	map = mapPtr;
//	init({ LDR_CHIP_SIZE_X,LDR_CHIP_SIZE_Y }, { LDR_CHIP_CNT_X,LDR_CHIP_CNT_Y }, "image/tileset.png", LDR_DEF_SPEED);
//	nowID = LDR_CHIP_BBL;
//	keyGetRng = EDIT_KEY_GET_DEF_RNG;
//	inputFlam = EDIT_KEY_GET_DEF_RNG;
//	ZeroMemory(keyData, sizeof(keyData));
//}
//
//EditCursor::EditCursor()
//{
//}
//
//EditCursor::~EditCursor()
//{
//}
//
//void EditCursor::Draw()
//{
//	if (((animCnt / 15) % 2))
//	{
//		Obj::Draw(nowID);
//	}
//	else
//	{
//		Obj::Draw(LDR_CHIP_EDIT);
//	}
//	animCnt++;
//}
//
//void EditCursor::Update()
//{
//	memcpy(oldKeyData, keyData, sizeof(keyData));
//	GetHitKeyStateAll(keyData);
//	if ((keyData[KEY_INPUT_X] ^ oldKeyData[KEY_INPUT_X]) & keyData[KEY_INPUT_X])
//	{
//		if (nowID < LDR_CHIP_PL)
//		{
//			nowID = (CHIP_TYPE)(nowID + 1);
//		}
//		else
//		{
//			nowID = LDR_CHIP_BLANK;
//		}
//	}
//	if ((keyData[KEY_INPUT_Z] ^ oldKeyData[KEY_INPUT_Z]) & keyData[KEY_INPUT_Z])
//	{
//		if (nowID > LDR_CHIP_BLANK)
//		{
//			nowID = (CHIP_TYPE)(nowID - 1);
//		}
//		else
//		{
//			nowID = LDR_CHIP_PL;
//		}
//	}
//	if ((keyData[KEY_INPUT_LSHIFT] ^ oldKeyData[KEY_INPUT_LSHIFT]) & keyData[KEY_INPUT_LSHIFT])
//	{
//		map.lock()->SetMapID(LDR_CHIP_BLANK, pos);
//	}
//
//	if ((keyData[KEY_INPUT_C] ^ oldKeyData[KEY_INPUT_C]) & keyData[KEY_INPUT_C])
//	{
//		map.lock()->SetMapID(nowID, pos);
//	}
//	posSt oldPos = pos;
//	posSt tmpPos = pos;;
//	// 一旦、仮移動させる
//	if (keyData[KEY_INPUT_NUMPAD8])
//	{
//		tmpPos.y -= LDR_CHIP_SIZE_Y;
//	}
//	if (keyData[KEY_INPUT_NUMPAD2])
//	{
//		tmpPos.y += LDR_CHIP_SIZE_Y;
//	}
//	if (keyData[KEY_INPUT_NUMPAD4])
//	{
//		tmpPos.x -= LDR_CHIP_SIZE_X;
//	}
//	if (keyData[KEY_INPUT_NUMPAD6])
//	{
//		tmpPos.x += LDR_CHIP_SIZE_X;
//	}
//
//	if ((tmpPos.x < 0) || (tmpPos.x >= LDR_MAP_SIZE_X*LDR_CHIP_SIZE_X)
//	 || (tmpPos.y < 0) || (tmpPos.y >= LDR_MAP_SIZE_Y*LDR_CHIP_SIZE_Y))
//	{
//		// 範囲外の場合は、移動をキャンセルにする。
//		tmpPos = oldPos;
//	}
//	if ((oldPos.x == tmpPos.x) && (oldPos.y == tmpPos.y))
//	{
//		// 移動していない場合は、ｷｰ入力がなかったとして、入力受付間隔を元に戻す
//		keyGetRng = EDIT_KEY_GET_DEF_RNG;
//		inputFlam = EDIT_KEY_GET_DEF_RNG;
//	}
//	else
//	{
//		// 仮移動していた場合は、受付ﾌﾚｰﾑに達しているかを確認し、
//		// 達していた場合、移動させ、経過ﾌﾚｰﾑはｸﾘｱしておく
//		if (inputFlam >= keyGetRng)
//		{
//			pos = tmpPos;
//			keyGetRng = (keyGetRng / 2 < 5 ? 5 : keyGetRng / 2);
//			inputFlam = 0;
//		}
//		else
//		{
//			inputFlam++;
//		}
//	}
//}

