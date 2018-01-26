//#pragma once
//#include <memory>
//#include "Obj.h"
//
//class Camera;
//class Player;
//class Enemy;
//
//typedef struct {
//	char fileID[13];	// �t�@�C����ID���
//	char verID;			// �t�@�C���̃o�[�W�����ԍ�
//	char sizeX;			// �}�b�v�̃T�C�YX
//	char sizeY;			// �}�b�v�̃T�C�YY
//	char sum;			// SUM�l
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
//	//�����ŉϒ��z��ɂ��Ȃ��͓̂G�̐������܂��Ă��邩��
//	//�ϒ��ɂ����ꍇ�������̍Ĕz�u�������Ă��܂��ă��������ŕs����N����\��������
//	//�����Ȃ�ƒǂ����炢�̂ŗ��R�̂Ȃ��ϒ��͂���Ȃ�!
//	std::shared_ptr<Enemy> enemy[ENEMY_MAX];
//	int enemyCnt;
//	posSt digPos;
//	bool digFlag;
//	int digCnt[LDR_MAP_SIZE_Y][LDR_MAP_SIZE_X];
//};

