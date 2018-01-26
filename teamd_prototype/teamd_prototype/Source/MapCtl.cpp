//using namespace std;
//#include "dxlib.h"
//#include <string.h>
//#include <string>
//#include "ImageManager.h"
//#include "MapCtl.h"
//#include "Camera.h"
//#include "Player.h"
//#include "Enemy.h"
//#include "EditCursor.h"
//#include "DataTbl.h"
//#include "main.h"
//
//MapCtl::MapCtl(PMODE *pModeID, weak_ptr<Camera> camPtr)
//{
//	cam = camPtr;
//	pMode = pModeID;
//	clearFlag = false;
//	digFlag = false;
//	enemyCnt = 0;
//	if (*pMode == PMODE_EDIT)
//	{
//		ZeroMemory(MapData, sizeof(MapData));
//	}
//	else
//	{
//		LoadMap();
//		SetUpChar();
//	}
//	init({ LDR_CHIP_SIZE_X,LDR_CHIP_SIZE_Y }, { LDR_CHIP_CNT_X,LDR_CHIP_CNT_Y }, "image/tileset.png", 0);
//}
//MapCtl::MapCtl()
//{
//
//}
//void MapCtl::SetUpChar(void)
//{
//	/*for (int y = 0; y < LDR_MAP_SIZE_Y; y++)
//	{
//		for (int x = 0; x < LDR_MAP_SIZE_X; x++)
//		{
//			for (int id = 0; id < EDIT_GP_MAX; id++)
//			{
//				int picID = (MapData[y][x] >> (MAP_DATA_SHIFT * id)) & 0x0000000f;
//			}
//		}
//	}*/
//	for (int y = 0; y < LDR_MAP_SIZE_Y; y++)
//	{
//		for (int x = 0; x < LDR_MAP_SIZE_X; x++)
//		{
//			for (int id = 0; id < EDIT_GP_MAX; id++)
//			{
//				int picID = (MapData[y][x] >> (MAP_DATA_SHIFT * id)) & 0x0000000f;
//				switch (picID)
//				{
//				case LDR_CHIP_PL:
//					player = std::make_shared < Player >(this, cam);
//					if (!cam.expired())
//					{
//						cam.lock()->SetTarget(player);
//					}
//					player->SetPos({ x*LDR_CHIP_SIZE_X, y*LDR_CHIP_SIZE_Y });
//					player->RePopPos({ x*LDR_CHIP_SIZE_X, y*LDR_CHIP_SIZE_Y });
//					objList.push_front(player);
//					break;
//				case LDR_CHIP_ENEMY:
//					enemy[enemyCnt] = std::make_shared < Enemy >(this, cam);
//					//ïsäÆëSå^ÉNÉâÉXÇÃÉ|ÉCÉìÉ^ÇÕÅ[Ç≈Ç´Ç‹ÇπÇÒÇ≈ÉGÉâÅ[Ç™ãNÇ±ÇÈóùóR
//					//includeÇµÇƒenemyèÓïÒÇìnÇµÇƒÇ»Ç¢Ç©ÇÁenemyÇÃì‡óeÇ™ÇÊÇ≠ÇÌÇ©ÇÁÇ¢Ç∆Ç¢Ç§Ç±Ç∆
//					enemy[enemyCnt]->SetPos({ x*LDR_CHIP_SIZE_X, y*LDR_CHIP_SIZE_Y });
//					enemy[enemyCnt]->RePopPos({ x*LDR_CHIP_SIZE_X, y*LDR_CHIP_SIZE_Y });
//					
//
//					//if (enemyCnt)
//					//{
//					objList.push_front(enemy[enemyCnt]);
//					//}
//
//					enemyCnt++;
//					
//
//					break;
//				default:
//					break;
//				}
//			}
//		}
//	}	
//}
//
//bool MapCtl::LoadMap(void)
//{
//	bool rtnFlag =false;
//	FILE *file;
//	DataHeader expData;
//	fopen_s(&file, "data/mapdata.map", "rb");
//	fread(&expData, sizeof(expData), 1, file);
//	fread(&MapData, sizeof(MapData), 1, file);
//	int tmpSum = 0;
//	for (int y = 0; y < LDR_MAP_SIZE_Y; y++)
//	{
//		for (int x = 0; x < LDR_MAP_SIZE_X; x++)
//		{
//			tmpSum += MapData[y][x];
//			digCnt[y][x] = 0;
//		}
//	}
//	tmpSum &= 0x0f;
//	if (tmpSum == expData.sum)
//	{
//		rtnFlag = true;
//	}
//	fclose(file);
//	return rtnFlag;
//}
//bool MapCtl::GetClearFlag(void)
//{
//	return clearFlag;
//}
//posSt MapCtl::GetPlayerPos(void)
//{
//	return player->GetPos();
//}
//bool MapCtl::HitPlayerToEnemy(void)
//{
//	
//	for (int i = 0; i < enemyCnt; i++)
//	{
//		if (enemy[i]->GetState() != ST_DETH)
//		{
//			posSt playerPos = player->GetPos();
//			posSt enemyPos = { enemy[i]->GetPos().x + enemy[i]->GetSize().x / 2, enemy[i]->GetPos().y + enemy[i]->GetSize().y / 2 };
//			posSt playerSize = player->GetSize();
//
//			if (playerPos.x                   <= enemyPos.x
//				&& playerPos.x + playerSize.x >= enemyPos.x
//				&& playerPos.y                <= enemyPos.y
//				&& playerPos.y + playerSize.y >= enemyPos.y)
//			{
//				return true;
//			}
//		}
//
//	}
//	
//	
//	return false;
//}
//bool MapCtl::HitFallPlayerToEnemy(void)
//{
//	for (int i = 0; i < enemyCnt; i++)
//	{
//		if (enemy[i]->GetState() != ST_DETH)
//		{
//			posSt playerSize = player->GetSize();
//			posSt enemySize = enemy[i]->GetSize();
//			posSt playerPos = { player->GetPos().x, player->GetPos().y + playerSize.y - 1 + player->GetSpeed()};
//			posSt enemyPos = enemy[i]->GetPos();
//			
//
//			if ((playerPos.x                  <= enemyPos.x + enemySize.y
//				|| playerPos.x + playerSize.x >= enemyPos.x)
//				&&playerPos.y                 <= enemyPos.y + enemySize.y
//				&& playerPos.y + playerSize.y >= enemyPos.y)
//				
//			{
//				return true;
//			}
//		}
//
//	}
//
//
//	return false;
//}
//bool MapCtl::HitFallEnemyToEnemy(Enemy *EnemyA)
//{
//	for (int i = 0; i < enemyCnt; i++)
//	{
//			if (enemy[i]->GetState() != ST_DETH && (EnemyA->GetPos().x != enemy[i]->GetPos().x && EnemyA->GetPos().y != enemy[i]->GetPos().y))
//			{
//				posSt enemyASize = EnemyA->GetSize();
//				posSt enemyBSize = enemy[i]->GetSize();
//				posSt enemyAPos = { EnemyA->GetPos().x, EnemyA->GetPos().y + enemyASize.y - 1 + EnemyA->GetSpeed() };
//				posSt enemyBPos = enemy[i]->GetPos();
//
//
//				if ((enemyAPos.x                  <= enemyBPos.x + enemyBSize.y
//					|| enemyAPos.x + enemyASize.x >= enemyBPos.x)
//					&& enemyAPos.y                <= enemyBPos.y + enemyBSize.y
//					&& enemyAPos.y + enemyASize.y >= enemyBPos.y)
//
//				{
//					return true;
//				}
//			}
//		}
//	return false;
//
//	}
//void MapCtl::CharReset(void)
//{
//	int cunt = 0;
//
//	for (int y = 0; y < LDR_MAP_SIZE_Y; y++)
//	{
//		for (int x = 0; x < LDR_MAP_SIZE_X; x++)
//		{
//			for (int id = 0; id < EDIT_GP_MAX; id++)
//			{
//				int picID = (MapData[y][x] >> (MAP_DATA_SHIFT * id)) & 0x0000000f;
//				switch (picID)
//				{
//				case LDR_CHIP_PL:
//					player->SetPos({ x*LDR_CHIP_SIZE_X, y*LDR_CHIP_SIZE_Y });
//					break;
//				case LDR_CHIP_ENEMY:
//					enemy[cunt]->SetPos({ x*LDR_CHIP_SIZE_X, y*LDR_CHIP_SIZE_Y });
//
//					cunt++;
//
//					break;
//				default:
//					break;
//				}
//			}
//		}
//	}
//}
//void MapCtl::SaveMap(void)
//{
//	DataHeader expData = { "LDR_MAP_DATA",LDR_VER_ID,LDR_MAP_SIZE_X,LDR_MAP_SIZE_Y,0 };
//	for (int y = 0; y < LDR_MAP_SIZE_Y; y++)
//	{
//		for (int x = 0; x < LDR_MAP_SIZE_X; x++)
//		{
//			expData.sum += MapData[y][x];
//		}
//	}
//	expData.sum &= 0x0f;
//
//	FILE *file;
//	fopen_s(&file, "data/mapdata.map", "wb");
//	fwrite(&expData, sizeof(expData), 1, file);
//	fwrite(MapData, sizeof(MapData), 1, file);
//	fclose(file);
//}
//
//void MapCtl::Draw()
//{
//	bool goldFlag = false;
//	if (*pMode == PMODE_GAME)
//	{
//		animCnt++;
//	}
//	for (int y = 0; y < LDR_MAP_SIZE_Y; y++)
//	{
//		for (int x = 0; x < LDR_MAP_SIZE_X; x ++)
//		{
//			pos = { x * LDR_CHIP_SIZE_X,y * LDR_CHIP_SIZE_Y };
//			for (int id = 0; id < EDIT_GP_MAX; id++)
//			{
//				int picID = (MapData[y][x] >> (MAP_DATA_SHIFT * id)) & 0x0000000f;
//				// íEèo º∫ﬁÇÃèÍçáÅA∏ÿ±Ã◊∏ﬁÇ™trueÇ≈Ç»ÇØÇÍÇŒï`âÊÇµÇ»Ç¢
//				switch (picID)
//				{
//				case LDR_CHIP_GOLD:
//					
//					goldFlag = true;
//					break;
//				case LDR_CHIP_ESC:
//					if (*pMode == PMODE_GAME)
//					{
//						if (!clearFlag || clsLadCnt > pos.y)
//						{
//							continue;
//						}
//						else
//						{
//							picID = LDR_CHIP_LAD;
//						}
//					}
//					break;
//				case LDR_CHIP_TRAP:
//					if (*pMode == PMODE_GAME)
//					{
//						// ƒ◊ØÃﬂÇÕπﬁ∞—”∞ƒﬁéûÇÕí èÌÃﬁ€Ø∏Ç∆ÇµÇƒï`âÊÇ∑ÇÈ
//						picID = LDR_CHIP_BBL;
//					}
//					break;
//				default:
//					break;
//				}
//				switch (DrawModeTbl[picID])
//				{
//				case DRAW_ALL:	// èÌÇ…ï`âÊ
//					break;
//				case DRAW_EDIT:	// ¥√ﬁ®ØƒéûÇÃÇ›
//					if (*pMode == PMODE_GAME)
//					{
//						continue;
//					}
//					break;
//				case DRAW_GAME:	// πﬁ∞—íÜÇÃÇ›
//					if (*pMode == PMODE_EDIT)
//					{
//						continue;
//					}
//					break;
//				case DRAW_NON:	// ï`âÊÇµÇ»Ç¢
//				default:
//					continue;
//				}
//				if ((picID == LDR_CHIP_LAD) || (picID == LDR_CHIP_GOLD))
//				{
//					picID += (abs(2 - (int)((animCnt / 10) % 4))*LDR_CHIP_CNT_X);
//				}
//
//				if (*pMode == PMODE_GAME)
//				{
//					if (picID == LDR_CHIP_BBL)
//					{
//						UpdateDig({ x,y });
//						if (digCnt[y][x] == 0)
//						{
//							// âΩÇ‡ÇµÇ»Ç¢
//						}
//						else if (digCnt[y][x] < DIG_SPEED * DIG_STEP_MAX)
//						{
//							picID += (((digCnt[y][x] / DIG_SPEED) + 1)*LDR_CHIP_CNT_X);
//							pos.y -= LDR_CHIP_SIZE_Y;
//							Obj::Draw((((digCnt[y][x] / DIG_SPEED) + 1)*LDR_CHIP_CNT_X) + 6);
//							pos.y += LDR_CHIP_SIZE_Y;
//						}
//						else if (digCnt[y][x] < DIG_SPEED * DIG_STEP_MAX + DAG_START_CNT)
//						{
//							picID = LDR_CHIP_BLANK;
//						}
//						else
//						{
//							int tmpCnt = digCnt[y][x] - (DIG_SPEED * DIG_STEP_MAX + DAG_START_CNT);
//							picID += ((DIG_STEP_MAX - (tmpCnt / DAG_SPEED))*LDR_CHIP_CNT_X + 1);
//						}
//					}
//				}
//				Obj::Draw(picID);
//			}
//			if (*pMode == PMODE_EDIT)
//			{
//				posSt camSize = cam.lock()->GetGmScrSize();
//				posSt scrPos = cam.lock()->GetPos();
//				scrPos.x -= (camSize.x / 2);
//				scrPos.y -= (camSize.y / 2);
//				if (((pos.x) >= scrPos.x - size.x * 2) && (pos.x - scrPos.x <= SCREEN_SIZE_X)
//					&& ((pos.y - size.y) >= scrPos.y) && (pos.y <= scrPos.y + camSize.y))
//				{
//					DrawBox((SCREEN_SIZE_X - camSize.x) / 2 + pos.x - scrPos.x, pos.y - scrPos.y,
//							(SCREEN_SIZE_X - camSize.x) / 2 + pos.x - scrPos.x + size.x, pos.y - scrPos.y + size.y,
//							GetColor(255, 255, 255), false);
//				}
//			}
//		}
//	}
//	if (goldFlag == false)
//	{
//		if (!clearFlag)
//		{
//			clsLadCnt = SCREEN_SIZE_Y;
//		}
//		else
//		{
//			clsLadCnt = (clsLadCnt > 0 ? clsLadCnt - LDR_CHIP_SIZE_Y/2 : 0);
//		}
//
//		bool tmpFlg = false;
//
//		for (int i = 0; i < enemyCnt; i++)
//		{
//			//ìGÇ™ã‡âÚÇéùÇ¡ÇƒÇ¢ÇΩÇÁ
//			if (enemy[i]->GetGoldFlg())
//			{
//				tmpFlg = true;
//				break;
//			}
//			
//		}
//
//		if (!tmpFlg)
//		{
//			clearFlag = true;
//		}
//		
//	}
//}
//
//void MapCtl::Update(void)
//{
//	if (*pMode == PMODE_EDIT)
//	{
//		if (CheckHitKey(KEY_INPUT_F5))
//		{
//			SaveMap();
//		}
//		if (CheckHitKey(KEY_INPUT_F6))
//		{
//			if (LoadMap() == false)
//			{
//				ZeroMemory(MapData, sizeof(MapData));
//			}
//		}
//	}
//
//}
//
//unsigned int MapCtl::GetMapID(posSt idPos)
//{
//	posSt tmpPos = { idPos.x / LDR_CHIP_SIZE_X,idPos.y / LDR_CHIP_SIZE_Y };
//	if (tmpPos.x >= 0 && tmpPos.x < LDR_MAP_SIZE_X && tmpPos.y >= 0 && tmpPos.y < LDR_MAP_SIZE_Y)
//	{
//		return MapData[tmpPos.y][tmpPos.x];
//	}
//
//	// îÕàÕäOÇÃèÍçáÇÕâÛÇπÇ»Ç¢ï«Çï‘Ç∑
//	return LDR_CHIP_BL;
//}
//void MapCtl::startDig(posSt setPos)
//{
//	digFlag = true;
//	digPos = { (setPos.x / LDR_CHIP_SIZE_X),(setPos.y / LDR_CHIP_SIZE_Y)};
//	if (digPos.x >= 0 && digPos.x < LDR_MAP_SIZE_X
//	 && digPos.y >= 0 && digPos.y < LDR_MAP_SIZE_Y)
//	{
//		digCnt[digPos.y][digPos.x] = 1;
//	}
//}
//void MapCtl::UpdateDig(posSt setPos)
//{
//	if (digCnt[setPos.y][setPos.x] > 0)
//	{
//		digCnt[setPos.y][setPos.x]++;
//		if (digCnt[setPos.y][setPos.x] >= DIG_SPEED * DIG_STEP_MAX + DAG_START_CNT + DIG_STEP_MAX * DAG_SPEED)
//		{
//			digCnt[setPos.y][setPos.x] = 0;
//		}
//	}
//}
//bool MapCtl::checkDig(void)
//{
//	if( digPos.x >= 0 && digPos.x < LDR_MAP_SIZE_X
//	 && digPos.y >= 0 && digPos.y < LDR_MAP_SIZE_Y)
//	if (digCnt[digPos.y][digPos.x] >= DIG_SPEED * DIG_STEP_MAX)
//	{
//		//å@ÇËèIÇ¶ÇƒÇ¢ÇÈ
//		digFlag = false;
//	}
//	return digFlag;
//}
//bool MapCtl::checkBlockState(DIR tmpDir, int tmpSpeed, posSt ckPos)
//{
//	bool rtnFlag = false;
//	posSt tmpPos = ckPos;
//	switch (tmpDir)
//	{
//	case DIR_LEFT:
//		tmpPos.x -= tmpSpeed;
//		break;
//	case DIR_RIGHT:
//		tmpPos.x += (GetSize().x > tmpSpeed ? GetSize().x : tmpSpeed);
//		break;
//	case DIR_UP:
//		tmpPos.y -= tmpSpeed;
//		break;
//	case DIR_DOWN:
//		tmpPos.y += (GetSize().y > tmpSpeed ? GetSize().y : tmpSpeed);
//		break;
//	case DIR_NON:
//		// âΩÇ‡ÇµÇ»Ç¢
//		break;
//	default:
//		// âΩÇ‡ÇµÇ»Ç¢
//		break;
//	}
//
//	tmpPos.x = tmpPos.x / LDR_CHIP_SIZE_X;
//	tmpPos.y = tmpPos.y / LDR_CHIP_SIZE_Y;
//	if (tmpPos.x >= 0 && tmpPos.x < LDR_MAP_SIZE_X
//		&& tmpPos.y >= 0 && tmpPos.y < LDR_MAP_SIZE_Y)
//	{
//		if (digCnt[tmpPos.y][tmpPos.x] == 0)
//		{
//			rtnFlag = true;
//		}
//	}
//	return rtnFlag;
//
//}
//bool MapCtl::CheckID(posSt ckPos, CHIP_TYPE ckType,bool bkFlag)
//{
//	int tmp = ((GetMapID(ckPos) >> (MAP_DATA_SHIFT * editGpTbl[ckType])) & 0x000000ff);
//	if (ckType == LDR_CHIP_BLANK)
//	{
//		if (GetMapID(ckPos) == 0 || (CheckID(ckPos, LDR_CHIP_ESC, true) && !clearFlag)
//		 || CheckID(ckPos, LDR_CHIP_PL) || CheckID(ckPos, LDR_CHIP_ENEMY))
//		{
//			return true;
//		}
//	}
//	else
//	{
//		if (((GetMapID(ckPos) >> (MAP_DATA_SHIFT * editGpTbl[ckType])) & 0x000000ff) == ckType)
//		{
//			if ((ckType != LDR_CHIP_ESC) || clearFlag || (ckType == LDR_CHIP_ESC && bkFlag))
//			{
//				return true;
//			}
//		}
//	}
//	return false;
//}
//unsigned int MapCtl::GetMapID(DIR tmpDir,int tmpSpeed, posSt idPos)
//{
//	posSt tmpPos = idPos;
//	switch (tmpDir)
//	{
//	case DIR_LEFT:
//		tmpPos.x -= tmpSpeed;
//		break;
//	case DIR_RIGHT:
//		tmpPos.x += (GetSize().x > tmpSpeed ? GetSize().x:tmpSpeed);
//		break;
//	case DIR_UP:
//		tmpPos.y -= tmpSpeed;
//		break;
//	case DIR_DOWN:
//		tmpPos.y += (GetSize().y > tmpSpeed ? GetSize().y : tmpSpeed);
//		break;
//	case DIR_NON:
//		// âΩÇ‡ÇµÇ»Ç¢
//		break;
//	default:
//		// âΩÇ‡ÇµÇ»Ç¢
//		break;
//	}
//	return GetMapID(tmpPos);
//}
//
//#define SET_MAP_DATA(X) ((MapData[selY][selX] & (0x000000ff<< (MAP_DATA_SHIFT * X))) | tmpID)
//bool MapCtl::SetMapID(CHIP_TYPE wall_ID, posSt idPos)
//{
//	bool flag = false;
//	int selX = (idPos.x / LDR_CHIP_SIZE_X);
//	int selY = (idPos.y / LDR_CHIP_SIZE_Y);
//
//	if ((idPos.x >=0) && (selX < LDR_MAP_SIZE_X)
//	 && (idPos.y >=0) && (selY < LDR_MAP_SIZE_Y))
//	{
//		unsigned int tmpID = (wall_ID << (MAP_DATA_SHIFT * editGpTbl[wall_ID]));
//		switch (editGpTbl[wall_ID])
//		{
//			case EDIT_GP_MAP:	// OBJÇ∆ã§ë∂Ç≈Ç´ÇÈ
//				MapData[selY][selX] = SET_MAP_DATA(EDIT_GP_OBJ);
//				break;
//			case EDIT_GP_ONLY:	// ëºÇ∆ã§ë∂Ç≈Ç´Ç»Ç¢
//				MapData[selY][selX] = tmpID;
//				break;
//			case EDIT_GP_OBJ:		// OBJ
//				MapData[selY][selX] = SET_MAP_DATA(EDIT_GP_MAP);
//				break;
//			default:
//				break;
//		}
//		flag = true;
//	}
//	return flag;
//}
//bool MapCtl::ClearObjID(posSt idPos)
//{
//	bool flag = false;
//	int selX = (idPos.x / LDR_CHIP_SIZE_X);
//	int selY = (idPos.y / LDR_CHIP_SIZE_Y);
//
//	if ((idPos.x >= 0) && (selX < LDR_MAP_SIZE_X)
//		&& (idPos.y >= 0) && (selY < LDR_MAP_SIZE_Y))
//	{
//		MapData[selY][selX] = MapData[selY][selX] & 0x00ffff;
//		flag = true;
//	}
//	return flag;
//}
//
//MapCtl::~MapCtl()
//{
//}
