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
		"../Sound/musmus/BGM/tutrialBGM.mp3",			// BGM_TUTRIAL	�FtutrialBGM
		"../Sound/musmus/BGM/titleBGM.mp3",				// BGM_TITLE	�FtitleBGM
		"../Sound/musmus/BGM/resultBGM.mp3",			// BGM_RESULT	�FresultBGM
		"../Sound/musmus/BGM/gameBGM.mp3",				// BGM_GAME		�FgameBGM
		"../Sound/musmus/Button/btn1.mp3",				// BUTTON_1		�Ftitle,result�Ɏg�p����button
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
		"../Sound/bakuhatu.wav"//�܂��Ȃ��ł�			// EXPLOSION,
	};

	for (int i = 0; i < SOUND_MAX; i++)
	{
		sound[i] = LoadSoundMem(filePath[i]);
	}
}

//----------------------------------------
//	�w��T�E���h�̍Đ�
//----------------------------------------
void SoundManager::Play(SOUND_TYPE _type, int _volume)
{
	ChangeVolumeSoundMem(_volume, sound[_type]);
	PlaySoundMem(sound[_type], DX_PLAYTYPE_BACK);
}

//----------------------------------------
//	�w��T�E���h��Loop�Đ�
//----------------------------------------
void SoundManager::PlayLoop(SOUND_TYPE _type, int _volume)
{
	ChangeVolumeSoundMem(_volume, sound[_type]);
	PlaySoundMem(sound[_type], DX_PLAYTYPE_LOOP);
}

//----------------------------------------
//	�w��T�E���h�̍Đ�Cheak
//----------------------------------------
bool SoundManager::PlayCheak(SOUND_TYPE _type)
{
	if (CheckSoundMem(sound[_type]) == 1)
	{
		//�Đ���
		return true;
	}
	else if(CheckSoundMem(sound[_type]) == 0)
	{
		//��~��
		return false;
	}
	else
	{
		printfDx("�T�E���h�G���[����");
	}
}

//----------------------------------------
//	�w��T�E���h�̒�~
//----------------------------------------
void SoundManager::Stop(SOUND_TYPE _type)
{
	StopSoundMem(sound[_type]);
}