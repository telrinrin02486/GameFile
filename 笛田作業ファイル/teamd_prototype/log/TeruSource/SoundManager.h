#pragma once


//soundの種類
//まだ追加してません
enum SOUND_TYPE
{
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
	void Stop(SOUND_TYPE _type);							//再生中soundの停止
};

