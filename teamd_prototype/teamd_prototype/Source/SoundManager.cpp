#include "SoundManager.h"
#include "DxLib.h"

//----------------------------------------
//	
//----------------------------------------
SoundManager::SoundManager()
{
}

//----------------------------------------
//	
//----------------------------------------
SoundManager::~SoundManager()
{
}

//----------------------------------------
//	
//----------------------------------------
void SoundManager::Initialize()
{
	char filePath[SOUND_MAX][256] =
	{
		"../Sound/musmus/BGM/tutrialBGM.mp3",			// BGM_TUTRIAL	：tutrialBGM
		"../Sound/musmus/BGM/titleBGM.mp3",				// BGM_TITLE	：titleBGM
		"../Sound/musmus/BGM/resultBGM.mp3",			// BGM_RESULT	：resultBGM
		"../Sound/musmus/BGM/gameBGM.mp3",				// BGM_GAME		：gameBGM
		"../Sound/musmus/Button/btn1.mp3",				// BUTTON_1		：title,resultに使用するbutton
		"../Sound/musmus/Button/btn2.mp3",				// BUTTON_2
		"../Sound/musmus/SceneSwitch/st012.mp3",		// SS_1
		"../Sound/taira-komori/SceneSwitch/Cute.mp3",	// SS_2
		"../Sound/other/whistle.mp3",					// SE_WHISTLE
		"../Sound/taira-komori/SE/Kick.mp3",			// SE_STEPS
		"../Sound/On-Jin/BloodSplash.mp3",				// SE_BLOOD
		"../Sound/On-Jin/collapse.mp3",					// SE_MASH
		"../Sound/On-Jin/Fall.mp3",						// SE_FALL
		"../Sound/vita-chi/Scream/Man.wav",				// SCR_MAN
		"../Sound/vita-chi/Scream/Woman.wav",			// SCR_WOMAN

		"../Sound/hit1.wav",							// HIT_1,
		"../Sound/tenka.wav",							// TENKA,
		"../Sound/bakuhatu.wav"//まだないです			// EXPLOSION,
	};

	for (int i = 0; i < SOUND_MAX; i++)
	{
		sound[i] = LoadSoundMem(filePath[i]);
	}
}

//----------------------------------------
//	指定サウンドの再生
//----------------------------------------
void SoundManager::Play(SOUND_TYPE _type, int _volume)
{
	ChangeVolumeSoundMem(_volume, sound[_type]);
	PlaySoundMem(sound[_type], DX_PLAYTYPE_BACK);
}

//----------------------------------------
//	指定サウンドのLoop再生
//----------------------------------------
void SoundManager::PlayLoop(SOUND_TYPE _type, int _volume)
{
	ChangeVolumeSoundMem(_volume, sound[_type]);
	PlaySoundMem(sound[_type], DX_PLAYTYPE_LOOP);
}

//----------------------------------------
//	指定サウンドの再生Cheak
//----------------------------------------
bool SoundManager::PlayCheak(SOUND_TYPE _type)
{
	if (CheckSoundMem(sound[_type]) == 1)
	{
		//再生中
		return true;
	}
	else if(CheckSoundMem(sound[_type]) == 0)
	{
		//停止中
		return false;
	}
	else
	{
		printfDx("サウンドエラー発生");
	}
}

//----------------------------------------
//	指定サウンドの停止
//----------------------------------------
void SoundManager::Stop(SOUND_TYPE _type)
{
	StopSoundMem(sound[_type]);
}