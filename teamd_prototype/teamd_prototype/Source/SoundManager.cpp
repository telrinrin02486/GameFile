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
		"../Sound/musmus/BGM/tutrialBGM.mp3",		//tutrialBGM
		"../Sound/musmus/BGM/titleBGM.mp3",			//titleBGM
		"../Sound/musmus/BGM/resultBGM.mp3",		//resultBGM
		"../Sound/musmus/BGM/gameBGM.mp3",			//gameBGM
		"../Sound/musmus/Button/btn02.mp3",
		"../Sound/musmus/Button/btn16.mp3",
		"../Sound/musmus/SceneSwitch/st012.mp3",
		"../Sound/taira-komori/SceneSwitch/Cute.mp3",
		"../Sound/other/whistle.mp3",
		"../Sound/taira-komori/SE/Kick.mp3",
		"../Sound/vita-chi/Scream/Man.wav",
		"../Sound/vita-chi/Scream/Woman.wav",

		"../Sound/hit1.wav",
		"../Sound/tenka.wav",
		"../Sound/bakuhatu.wav"//�܂��Ȃ��ł�
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
		return true;
	}
	else
	{
		return false;
	}
	/*if (CheckSoundMem(sound[_type]) == 1)
	{
		return true;
	}
	else if(CheckSoundMem(sound[_type]) == 0)
	{
		return false;
	}
	else
	{
		printfDx("�T�E���h�G���[����");
	}*/
}

//----------------------------------------
//	�w��T�E���h�̒�~
//----------------------------------------
void SoundManager::Stop(SOUND_TYPE _type)
{
	StopSoundMem(sound[_type]);
}