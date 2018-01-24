#pragma once


//soundの種類
//まだ追加してません
enum SOUND_TYPE
{
	BGM_TUTRIAL,	//tutrialBGM
	BGM_TITLE,		//titleBGM
	BGM_RESULT,		//resultBGM
	BGM_GAME,		//gameBGM
	BUTTON_1,		//title,resultに使用するbutton
	BUTTON_2,
	SS_1,
	SS_2,
	SE_WHISTLE,
	SE_STEPS,
	SCR_MAN,
	SCR_WOMAN,

	HIT_1,
	TENKA,
	EXPLOSION,

	SOUND_MAX

};

class SoundManager
{
private:

	int sound[SOUND_MAX];

	
	SoundManager();		
	~SoundManager();	
	SoundManager(const SoundManager &Inst);				
	SoundManager & operator=(const SoundManager &Inst); 

public:

	
	static SoundManager &GetInstance()
	{
		static SoundManager Instance;
		return Instance;
	}

	void Initialize();
	void Play(SOUND_TYPE _type, int _volume = 128);			//指定soundの再生(1回)
	void PlayLoop(SOUND_TYPE _type, int _volume = 128);		//指定soundの再生(Loop)
	bool PlayCheak(SOUND_TYPE _type);						//指定soundの再生Cheak
	void Stop(SOUND_TYPE _type);							//再生中soundの停止
};

