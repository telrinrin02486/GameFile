//#pragma once
//#include <memory>
//#include "Obj.h"
//
//class Camera;
//class Player;
//class Enemy;
//
//typedef struct {
//	char fileID[13];	// ファイルのID情報
//	char verID;			// ファイルのバージョン番号
//	char sizeX;			// マップのサイズX
//	char sizeY;			// マップのサイズY
//	char sum;			// SUM値
//}DataHeader;
//
//#define LDR_VER_ID 0
//#define DIG_SPEED 6
//#define DIG_STEP_MAX 5
//#define DAG_START_CNT 300
//#define DAG_SPEED 36
//
//#define ENEMY_MAX 5
//class MapCtl :
//	public Obj
//{
//public:
//	MapCtl(PMODE *pModeID, std::weak_ptr<Camera> camPtr);
//	virtual ~MapCtl();
//	void Draw();
//	void Update();
//	bool LoadMap(void);
//	void SaveMap(void);
//	unsigned int GetMapID(posSt idPos);
//	unsigned int GetMapID(DIR tmpDir, int tmpSpeed, posSt idPos);
//	bool SetMapID(CHIP_TYPE wall_ID, posSt idPos);
//	bool ClearObjID(posSt idPos);
//	void SetUpChar(void);
//	void startDig(posSt setPos);
//	bool checkDig(void);
//	bool checkBlockState(DIR tmpDir, int tmpSpeed, posSt ckPos);
//	bool CheckID(posSt ckPos, CHIP_TYPE ckType,bool bkFlag = false);
//	bool GetClearFlag(void);
//	posSt GetPlayerPos(void);
//	bool HitPlayerToEnemy(void);
//	bool HitFallPlayerToEnemy(void);
//	bool HitFallEnemyToEnemy(Enemy *EnemyA);
//	void CharReset(void);
//
//
//private:
//	MapCtl();
//	void UpdateDig(posSt setPos);
//	PMODE *pMode;
//	unsigned int MapData[LDR_MAP_SIZE_Y][LDR_MAP_SIZE_X];
//	bool clearFlag;
//	int clsLadCnt;
//	std::shared_ptr<Player> player;
//	//ここで可変長配列にしないのは敵の数が決まっているから
//	//可変長にした場合メモリの再配置がおきてしまってメモリ内で不具合が起きる可能性がある
//	//こうなると追いずらいので理由のない可変長はつかわない!
//	std::shared_ptr<Enemy> enemy[ENEMY_MAX];
//	int enemyCnt;
//	posSt digPos;
//	bool digFlag;
//	int digCnt[LDR_MAP_SIZE_Y][LDR_MAP_SIZE_X];
//};

