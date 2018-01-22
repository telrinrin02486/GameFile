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
		"../Sound/musmus/BGM/BT_GIRLS.mp3",
		"../Sound/musmus/BGM/MouseParty.mp3",
		"../Sound/musmus/BGM/Omen.mp3",
		"../Sound/musmus/BGM/SakuraSkip.mp3",
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
		"../Sound/bakuhatu.wav"//‚Ü‚¾‚È‚¢‚Å‚·
	};


	for (int i = 0; i < SOUND_MAX; i++)
	{
		sound[i] = LoadSoundMem(filePath[i]);
	}
}

//----------------------------------------
//	
//----------------------------------------
void SoundManager::Play(SOUND_TYPE _type, int _volume)
{
	ChangeVolumeSoundMem(_volume, sound[_type]);
	PlaySoundMem(sound[_type], DX_PLAYTYPE_BACK);
}

//----------------------------------------
//	
//----------------------------------------
void SoundManager::PlayLoop(SOUND_TYPE _type, int _volume)
{
	ChangeVolumeSoundMem(_volume, sound[_type]);
	PlaySoundMem(sound[_type], DX_PLAYTYPE_LOOP);
}

//----------------------------------------
//	
//----------------------------------------
void SoundManager::Stop(SOUND_TYPE _type)
{
	StopSoundMem(sound[_type]);
}